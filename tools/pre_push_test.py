import os
import re
import json
from typing import List, Dict, Set, Union
import ast
import glob

class CodeChecker:
    def __init__(self):
        # Common rules for all file types
        self.common_rules = {
            'max_line_length': 150,
            'no_trailing_whitespace': True,
            'no_multiple_empty_lines': True,
            'require_newline_at_end': True
        }

        # File-specific rules
        self.python_rules = {
            'indent_size': 4,
            'require_docstrings': True,
            'no_star_imports': True
        }

        self.typescript_rules = {
            'indent_size': 4,
            'require_semicolons': True,
            'no_var_keyword': True
        }

        self.cpp_rules = {
            'indent_size': 4,
            'require_braces': True,
            'snake_case_functions': True
        }

        self.header_rules = {
            'guard_defines': True,
            'no_pragma_once': True,
            'require_header_comment': True
        }

        self.json_rules = {
            'indent_size': 4,
            'require_consistent_quotes': True,
            'disallow_comments': True,
            'disallow_trailing_comma': True,
            'max_nesting_depth': 8
        }

        # Directories to skip
        self.skip_directories = {
            'node_modules',
            'build',
            'dist',
            'venv',
            '.git',
            '__pycache__',
            '.vscode'
        }

    def check_file(self, filepath: str) -> List[str]:
        """
        Check a single file for style violations.
        Returns a list of violation messages.
        """
        if not os.path.exists(filepath):
            return [f"File not found: {filepath}"]

        _, ext = os.path.splitext(filepath)
        violations = []

        # Skip check if file is in excluded directory
        file_dir = os.path.dirname(filepath)
        if any(skip_dir in file_dir.split(os.sep) for skip_dir in self.skip_directories):
            return []

        # Read file content
        try:
            with open(filepath, 'r', encoding='utf-8') as f:
                content = f.read()
                lines = content.splitlines()
        except UnicodeDecodeError:
            return [f"Unable to read file {filepath}: Not a text file or invalid encoding"]

        # Check common rules
        violations.extend(self._check_common_rules(lines, filepath))

        # Check file-specific rules
        if ext == '.py':
            violations.extend(self._check_python_rules(content, lines, filepath))
        elif ext == '.ts':
            violations.extend(self._check_typescript_rules(content, lines, filepath))
        elif ext == '.cpp':
            violations.extend(self._check_cpp_rules(content, lines, filepath))
        elif ext == '.h':
            violations.extend(self._check_header_rules(content, lines, filepath))
        elif ext == '.json':
            violations.extend(self._check_json_rules(content, lines, filepath))

        return violations

    def _check_json_rules(self, content: str, lines: List[str], filepath: str) -> List[str]:
        """Check JSON-specific rules."""
        violations = []

        # First, validate JSON syntax
        try:
            json_content = json.loads(content)
        except json.JSONDecodeError as e:
            return [f"{filepath}:{e.lineno} Invalid JSON: {str(e)}"]

        # Check indentation
        current_indent = 0
        for i, line in enumerate(lines, 1):
            stripped_line = line.lstrip()
            if stripped_line:
                indent_size = len(line) - len(stripped_line)
                if indent_size % self.json_rules['indent_size'] != 0:
                    violations.append(
                        f"{filepath}:{i} Incorrect indentation. "
                        f"Must be multiple of {self.json_rules['indent_size']}"
                    )

        # Check quote consistency
        if self.json_rules['require_consistent_quotes']:
            quote_type = None
            for i, line in enumerate(lines, 1):
                # Find all strings in the line (excluding escaped quotes)
                matches = re.finditer(r'(?<!\\)"(?:[^"\\]|\\.)*"|(?<!\\)\'(?:[^\'\\]|\\.)*\'', line)
                for match in matches:
                    current_quote = match.group(0)[0]
                    if quote_type is None:
                        quote_type = current_quote
                    elif current_quote != quote_type:
                        violations.append(
                            f"{filepath}:{i} Inconsistent quote usage. "
                            f"Use {quote_type} throughout"
                        )

        # Check for comments
        if self.json_rules['disallow_comments']:
            for i, line in enumerate(lines, 1):
                stripped_line = line.strip()
                if stripped_line.startswith('//') or stripped_line.startswith('/*'):
                    violations.append(f"{filepath}:{i} Comments are not allowed in JSON")

        # Check for trailing commas
        if self.json_rules['disallow_trailing_comma']:
            for i, line in enumerate(lines, 1):
                stripped_line = line.strip()
                if re.search(r',\s*[}\]]', stripped_line):
                    violations.append(f"{filepath}:{i} Trailing comma found")

        # Check nesting depth
        def check_nesting_depth(obj: Union[Dict, List], current_depth: int = 0) -> int:
            if current_depth > self.json_rules['max_nesting_depth']:
                return current_depth
            
            if isinstance(obj, dict):
                return max(
                    [current_depth] + 
                    [check_nesting_depth(v, current_depth + 1) for v in obj.values()]
                )
            elif isinstance(obj, list):
                return max(
                    [current_depth] + 
                    [check_nesting_depth(item, current_depth + 1) for item in obj]
                )
            return current_depth

        max_depth = check_nesting_depth(json_content)
        if max_depth > self.json_rules['max_nesting_depth']:
            violations.append(
                f"{filepath} Maximum nesting depth exceeded "
                f"({max_depth} > {self.json_rules['max_nesting_depth']})"
            )

        # Check for consistent key ordering (if it's a dictionary at root level)
        if isinstance(json_content, dict):
            keys = list(json_content.keys())
            sorted_keys = sorted(keys)
            if keys != sorted_keys:
                violations.append(f"{filepath} Keys are not in alphabetical order")

        return violations

    def _check_common_rules(self, lines: List[str], filepath: str) -> List[str]:
        """Check rules that apply to all file types."""
        violations = []
        
        # Check line length
        for i, line in enumerate(lines, 1):
            if len(line) > self.common_rules['max_line_length']:
                violations.append(
                    f"{filepath}:{i} Line too long "
                    f"({len(line)} > {self.common_rules['max_line_length']})"
                )

        # Check trailing whitespace
        if self.common_rules['no_trailing_whitespace']:
            for i, line in enumerate(lines, 1):
                if line and line[-1].isspace():
                    violations.append(f"{filepath}:{i} Trailing whitespace")

        # Check multiple empty lines
        if self.common_rules['no_multiple_empty_lines']:
            empty_line_count = 0
            for i, line in enumerate(lines, 1):
                if not line.strip():
                    empty_line_count += 1
                else:
                    empty_line_count = 0
                if empty_line_count > 2:
                    violations.append(f"{filepath}:{i} Too many consecutive empty lines")

        # Check newline at end of file
        if self.common_rules['require_newline_at_end']:
            if lines and lines[-1].strip() == "":
                violations.append(f"{filepath} No newline at end of file")

        return violations

    def _check_python_rules(self, content: str, lines: List[str], filepath: str) -> List[str]:
        """Check Python-specific rules."""
        violations = []

        # Check indentation
        for i, line in enumerate(lines, 1):
            if line.startswith(' '):
                indent_size = len(line) - len(line.lstrip())
                if indent_size % self.python_rules['indent_size'] != 0:
                    violations.append(
                        f"{filepath}:{i} Incorrect indentation. "
                        f"Must be multiple of {self.python_rules['indent_size']}"
                    )

        # Check for docstrings
        if self.python_rules['require_docstrings']:
            try:
                tree = ast.parse(content)
                # Check module docstring
                if not ast.get_docstring(tree):
                    violations.append(f"{filepath}:1 Missing module docstring")
                
                # Check functions and classes
                for node in ast.walk(tree):
                    if isinstance(node, (ast.FunctionDef, ast.ClassDef)):
                        if not ast.get_docstring(node):
                            violations.append(
                                f"{filepath}:{node.lineno} Missing docstring in {node.name}"
                            )
            except SyntaxError as e:
                violations.append(f"{filepath}:{e.lineno} Python syntax error: {str(e)}")

        # Check for star imports
        if self.python_rules['no_star_imports']:
            for i, line in enumerate(lines, 1):
                if re.match(r'^\s*from\s+.*\s+import\s+\*', line):
                    violations.append(f"{filepath}:{i} Star import used")

        return violations

    def _check_typescript_rules(self, content: str, lines: List[str], filepath: str) -> List[str]:
        """Check TypeScript-specific rules."""
        violations = []

        # Check indentation
        for i, line in enumerate(lines, 1):
            if line.startswith(' '):
                indent_size = len(line) - len(line.lstrip())
                if indent_size % self.typescript_rules['indent_size'] != 0:
                    violations.append(
                        f"{filepath}:{i} Incorrect indentation. "
                        f"Must be multiple of {self.typescript_rules['indent_size']}"
                    )

        # Check semicolons
        if self.typescript_rules['require_semicolons']:
            for i, line in enumerate(lines, 1):
                stripped_line = line.strip()
                if (stripped_line and not stripped_line.endswith(';') 
                    and not stripped_line.endswith('{') 
                    and not stripped_line.endswith('}')
                    and not stripped_line.endswith('/')
                    and not stripped_line.startswith('import')
                    and not stripped_line.startswith('export')
                    and not stripped_line.endswith(',')):
                    violations.append(f"{filepath}:{i} Missing semicolon")

        # Check var keyword usage
        if self.typescript_rules['no_var_keyword']:
            for i, line in enumerate(lines, 1):
                if re.search(r'\bvar\s+', line):
                    violations.append(f"{filepath}:{i} 'var' keyword used")

        return violations

    def _check_cpp_rules(self, content: str, lines: List[str], filepath: str) -> List[str]:
        """Check C++ specific rules."""
        violations = []

        # Check indentation
        for i, line in enumerate(lines, 1):
            if line.startswith(' '):
                indent_size = len(line) - len(line.lstrip())
                if indent_size % self.cpp_rules['indent_size'] != 0:
                    violations.append(
                        f"{filepath}:{i} Incorrect indentation. "
                        f"Must be multiple of {self.cpp_rules['indent_size']}"
                    )

        # Check braces
        if self.cpp_rules['require_braces']:
            for i, line in enumerate(lines, 1):
                if re.search(r'\b(if|for|while|do)\b[^{]*$', line):
                    next_line = lines[i].strip() if i < len(lines) else ''
                    if not next_line.startswith('{'):
                        violations.append(f"{filepath}:{i} Missing braces for control statement")

        # Check snake_case for functions
        if self.cpp_rules['snake_case_functions']:
            function_pattern = r'\w+\s+([A-Za-z_][A-Za-z0-9_]*)\s*\([^)]*\)\s*{'
            for i, line in enumerate(lines, 1):
                matches = re.search(function_pattern, line)
                if matches:
                    func_name = matches.group(1)
                    if not re.match(r'^[a-z][a-z0-9_]*$', func_name):
                        violations.append(
                            f"{filepath}:{i} Function name '{func_name}' "
                            "should be in snake_case"
                        )

        return violations

    def _check_header_rules(self, content: str, lines: List[str], filepath: str) -> List[str]:
        """Check header file specific rules."""
        violations = []
        
        # Check header guards
        if self.header_rules['guard_defines']:
            file_upper = os.path.basename(filepath).upper().replace('.', '_')
            guard_name = f"{file_upper}"
            
            has_ifndef = any(f'#ifndef {guard_name}' in line for line in lines)
            has_define = any(f'#define {guard_name}' in line for line in lines)
            has_endif = any('#endif' in line for line in lines)
            
            if not (has_ifndef and has_define and has_endif):
                violations.append(f"{filepath} Missing or incorrect header guards EXPECTED: {guard_name}")

        # Check pragma once
        if self.header_rules['no_pragma_once']:
            for i, line in enumerate(lines, 1):
                if '#pragma once' in line:
                    violations.append(f"{filepath}:{i} #pragma once found (use header guards instead)")

        # Check header comment
        # if self.header_rules['require_header_comment']:
        #     has_header_comment = False
        #     for line in lines[:5]:  # Check first 5 lines
        #         if '/*' in line or '//' in line:
        #             has_header_comment = True
        #             break
        #     if not has_header_comment:
        #         violations.append(f"{filepath} Missing header comment")

        return violations

    def check_directory(self, directory: str) -> Dict[str, List[str]]:
        """
        Check all relevant files in a directory and its subdirectories.
        Returns a dictionary mapping filenames to lists of violations.
        """
        results = {}
        extensions = ('.py', '.ts', '.cpp', '.h', '.json')
        
        for root, dirs, files in os.walk(directory):
            # Remove excluded directories
            dirs[:] = [d for d in dirs if d not in self.skip_directories]
            
            for file in files:
                if file.endswith(extensions):
                    filepath = os.path.join(root, file)
                    violations = self.check_file(filepath)
                    if violations:
                        results[filepath] = violations
        
        return results

def main():
    """Main function to run the code checker."""
    import argparse
    GREEN = '\033[92m'
    RED = '\033[91m'
    RESET = '\033[0m'
    parser = argparse.ArgumentParser(description='Multi-language code style checker')
    parser.add_argument('path', nargs='?', default='.', help='File or directory to check')
    parser.add_argument('--verbose', '-v', action='store_true', help='Show detailed output')
    args = parser.parse_args()

    checker = CodeChecker()

    if os.path.isfile(args.path):
        violations = checker.check_file(args.path)
        if violations:
            for violation in violations:
                print(violation)
            print(f"{RED}Style violations found.{RESET}")
            exit(1)
    else:
        results = checker.check_directory(args.path)
        if results:
            for filepath, violations in results.items():
                if args.verbose:
                    print(f"\nChecking {filepath}:")
                for violation in violations:
                    print(violation)
            print(f"{RED}Style violations found.{RESET}")
            exit(1)
    if args.verbose:
        print(f"{GREEN}No style violations found.{RESET}")
    exit(0)

if __name__ == '__main__':
    main()
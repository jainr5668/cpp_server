import os

folder_path = "/home/ronak/cpp_server/fw/src"

for root, dirs, files in os.walk(folder_path):
    for file in files:
        file_path = os.path.join(root, file)
        file_content = open(file_path, "r").read()
        file_lines = file_content.split("\n")
        if len(file_lines) > 0:
            if file_lines[-1].strip() != "":
                open(file_path, "a").write("\n")
                print(file_path)
        else:
            open(file_path, "w").write("\n")
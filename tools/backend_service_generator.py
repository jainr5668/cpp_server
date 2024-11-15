import os, shutil

path = os.path.dirname(os.path.realpath(__file__))
files_path = os.path.realpath(os.path.join(path, "data/backend_service_generator"))
featrue_name =  input('Enter the feature name:')
titled_name = featrue_name[0].title() + featrue_name[1:]
feature_path = os.path.realpath(os.path.join(path, f"../backend/{featrue_name}"))
if not os.path.exists(feature_path):
    os.makedirs(feature_path)
for file in os.listdir(files_path):
    if file == "__pycache__":
        continue
    f = open(os.path.join(files_path, file), 'r').readlines()
    f1 = open(os.path.join(feature_path, file), 'w')
    for line in f:
        f1.writelines(line.replace('featrue_name', f'"/{featrue_name}"'))
        
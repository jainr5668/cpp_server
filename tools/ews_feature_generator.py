import os

path = os.path.dirname(os.path.realpath(__file__))
files_path = os.path.realpath(os.path.join(path, 'data/ews_feature_generator'))
featrue_name = input('Enter the feature name:')
titled_name = featrue_name[0].title() + featrue_name[1:]
feature_path = os.path.realpath(os.path.join(path, f'../ews/src/app/features/{featrue_name}'))
if not os.path.exists(feature_path):
    os.makedirs(feature_path)
for file in os.listdir(files_path):
    new_file_name = f'{os.path.join(feature_path, (featrue_name+"."+file[:-4] )if file not in ["public_api.ts.txt", "index.ts.txt"] else file[:-4])}'
    f = open(new_file_name, 'w')
    for lines in open(os.path.join(files_path, file), 'r').readlines():
        f.writelines(lines.replace("##", featrue_name).replace('$$', titled_name))
    f.close()
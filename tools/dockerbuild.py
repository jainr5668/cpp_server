import threading
import os


path = os.path.dirname(os.path.realpath(__file__))
backend_path = os.path.realpath(os.path.join(path, "../backend"))
docker_map = {}#{"ews": os.path.realpath(os.path.join(path, "../ews"))}
for service in os.listdir("backend"):
    service_path = os.path.join(backend_path, service)
    docker_map[service] = service_path


def dockerbuild(service_name, path):
    print(service_name, path)
    os.chdir(path)
    os.system(f'docker rmi -f {service_name.lower()}:latest')
    os.system(f"docker build  -t {service_name.lower()}:latest .")

print(len(docker_map.items()))
for service, path in docker_map.items():
    dockerbuild(service, path)

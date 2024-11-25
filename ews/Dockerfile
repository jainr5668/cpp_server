FROM ubuntu:20.04
RUN apt-get update && apt-get install -y curl
WORKDIR /code
COPY package.json package-lock.json* /code/
RUN set -uex; \
    apt-get install -y ca-certificates curl gnupg; \
    mkdir -p /etc/apt/keyrings; \
    curl -fsSL https://deb.nodesource.com/gpgkey/nodesource-repo.gpg.key \
     | gpg --dearmor -o /etc/apt/keyrings/nodesource.gpg; \
    NODE_MAJOR=18; \
    echo "deb [signed-by=/etc/apt/keyrings/nodesource.gpg] https://deb.nodesource.com/node_$NODE_MAJOR.x nodistro main" \
     > /etc/apt/sources.list.d/nodesource.list; \
    apt-get update; \
    apt-get install nodejs -y
RUN npm -g install npm@latest
RUN npm install -g @angular/cli@17
RUN npm install
COPY . /code
EXPOSE 80
CMD ["ng", "serve", "--host", "0.0.0.0", "--poll=2000", "--port", "80", "--disable-host-check"]
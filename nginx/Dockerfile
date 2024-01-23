
FROM alpine:3.18.5

RUN apk update && apk upgrade --no-cache  && apk add zsh openssl nginx --no-cache

RUN mkdir /etc/nginx/ssl

#RUN openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
#-subj "/C=ES/ST=Urduliz/L=Madrid/O=forever/OU=forever/CN=0.0.0.0" \
#  -keyout /etc/nginx/ssl/openssl.key  -out /etc/nginx/ssl/openssl.crt && \
#  chmod 600 /etc/nginx/ssl/*
 #Generar la clave privada
RUN openssl genpkey -algorithm RSA -out /etc/nginx/ssl/openssl.key

# Generar la solicitud de certificado (CSR)
RUN openssl req -new -key /etc/nginx/ssl/openssl.key -out /etc/nginx/ssl/openssl.csr -subj  \
    "/C=US/ST=Madrid/L=Urduliz/O=dugo/OU=difp/CN=0.0.0.0"

# Firmar el certificado con la clave privada (certificado autofirmado)
RUN openssl x509 -req -days 365 -in /etc/nginx/ssl/openssl.csr -signkey /etc/nginx/ssl/openssl.key -out /etc/nginx/ssl/openssl.crt

COPY conf/nginx.conf /etc/nginx/http.d/default.conf

COPY index.html /usr/share/nginx/html/

RUN chown -R nginx:nginx /usr/share/nginx/html/

RUN chmod -R 755 /usr/share/nginx/html/


RUN  chmod -R 755 /usr/share/nginx/html/index.html 

CMD ["nginx", "-g", "daemon off;"]


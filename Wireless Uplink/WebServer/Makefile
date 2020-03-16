.PHONY: login build push

all: login build push

build:
	docker build . -t magida/iot-uplink

push:
	docker push magida/iot-uplink

login:
	docker login

clean:
	echo "hello world"


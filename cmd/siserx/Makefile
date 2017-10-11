FILE = siserx.go

rpi: $(FILE)
	GOARM=7 GOARCH=arm GOOS=linux go build siserx.go

build:
	go build siserx.go

install:
	go install $(FILE)

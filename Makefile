

default: build

build: build.ninja
	@ninja

run: build
	@.build/pkmp "This is my text [[special|don't show]] line with a [[link]] in it" 30 

default: build

build: build.ninja
	@ninja

.PHONEY: run
run: index

index: build
	@.build/pkmp index wiki

link: build
	@.build/pkmp link "This is my text [[special|don't show]] line with a [[link]] in it" 30 

default: build

build: build.ninja
	@ninja

.PHONEY: run
run: index

index: build
	@.build/pkmp index .
	
alias: build
	@.build/pkmp alias .index_links

link: build
	@.build/pkmp link "This is my text [[special|don't show]] line with a [[link]] in it" 40 
	@.build/pkmp link "This is my text [[special|don't show]] line with a [[link]] in it" 20 
	@.build/pkmp link "This is my text [[special|don't show]] line with a [[link]] in it" 60 
	@.build/pkmp link "This is my text [[special|don't show]] line with a [[link]] in it" 0 
	@.build/pkmp link "[[special|don't show]]" 20

.PHONEY: run
grep-links: 
	grep -RnoP --include=*.md '(?<!`)\[\[.*?\]\]' . > .index_links
	

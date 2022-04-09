# gplaces - a simple terminal gemini client

Named after [Going Places](https://en.wikipedia.org/wiki/Going_Places_(Herb_Alpert_and_the_Tijuana_Brass_album)), the 1965 album by Herb Alpert and The Tijuana Brass.

## Overview
- configurable MIME type handlers
- "powerful" shell
- bookmarks
- variables
- command aliases
- VT100 compatible with ANSI escape sequences
- no exotic external dependencies, no NIH
	- ~GNU readline is fully optional~ bestline
	- openssl
	- libcurl
- internal pager for text & menus
- SSH-style TOFU with ~/.gplaces_hosts
- about *1k lines* of *C* code

## How to compile?
- clone this git repo
- just type `make` on any Unix compatible system
	- currently tested on
		- Linux
- type `make install` to install it on the system (defaults to /usr/local)

## How to contribute?
- send me pull-requests and I'll review and merge them :)
- if you wish to appear on the `help authors` command just add yourself there

## License
- [GPLv3](https://www.gnu.org/licenses/gpl-3.0.html)

## Statistic
Language|files|blank|comment|code
:-------|-------:|-------:|-------:|-------:
C|1|237|34|1091

## Help
Just type `help` when the client is running.

#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

alias ls='ls --color=auto'
PS1='[\u@\h \W]\$ '
export PATH=$PATH:~/.cabal/bin:~/.xmonad/bin

#export PATH="$PATH:$HOME/.rvm/bin" # Add RVM to PATH for scripting

#export PATH=$PATH:~/RubyMine-7.0/bin

export PATH="$PATH:$HOME/.rvm/bin" # Add RVM to PATH for scripting

# extend the history
export HISTFILESIZE=1000000
export HISTSIZE=2000000

# remove duplicates or empty lines from the history
export HISTCONTROL=ignoreboth
 
# combine multiline commands
shopt -s cmdhist

# merge session histories
shopt -s histappend

# enable colors
eval "`dircolors -b`"

# force ls to use color
alias ls='ls -hF --color=auto'

# highlight grep results
export GREP_OPTIONS='--color=auto'

# use colordiff instead of diff
command -v colordiff >/dev/null 2>&1 && alias diff="colordiff -u"

# colorized man pages
export LESS_TERMCAP_mb=$'\E[01;31m'
export LESS_TERMCAP_md=$'\E[01;31m'
export LESS_TERMCAP_me=$'\E[0m'
export LESS_TERMCAP_se=$'\E[0m' # end info
export LESS_TERMCAP_so=$'\E[01;42;30m' # head info
export LESS_TERMCAP_ue=$'\E[0m'
export LESS_TERMCAP_us=$'\E[01;32m'

export PATH="$PATH:$HOME/.rvm/bin" # Add RVM to PATH for scripting


export TERM=xterm-256color

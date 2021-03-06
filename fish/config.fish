#path
set -gx PATH /home/sandric/bin $PATH
set -gx GOPATH /home/sandric/go
set -gx PATH /home/sandric/go/bin $PATH
set -gx PATH /usr/lib/firefox $PATH

#aliases

alias ll='ls -la'
alias v='vim'
alias t='trans :uk -b'
alias d='docker'
alias l='less'

function md
  mkdir $argv
end

function rd
  rm -rf $argv
end

#git aliases
alias g='git'
alias gs='git status'
alias gg='git status'
alias gl='git log'

function gd
  git diff $argv
end

function ga
  git add $argv
end

function gc
  git commit -m "$argv"
end

function gp
  git push $argv
end


set -x TERM xterm-256color


#fzf settings
set -x FZF_DEFAULT_OPTS '--bind ctrl-a:abort,\ :accept'
fzf_key_bindings

set nocompatible              " be iMproved, required
filetype off                  " required

set shell=/bin/bash

set expandtab
set shiftwidth=2
set softtabstop=2

highlight LineNr ctermfg=grey
set number

"set t_Co=256
"color github

hi visual ctermbg=81

" set the runtime path to include vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

" " alternatively, pass a path where Vundle should install plugins
" "call vundle#begin('~/some/path/here')
"
" " let Vundle manage Vundle, required
Plugin 'gmarik/Vundle.vim'

"
" " The following are examples of different formats supported.
" " Keep Plugin commands between vundle#begin/end.
" " plugin on GitHub repo
Plugin 'tpope/vim-fugitive'

" " plugin from http://vim-scripts.org/vim/scripts.html
" Plugin 'L9'
" " Git plugin not hosted on GitHub
Plugin 'git://git.wincent.com/command-t.git'

" " git repos on your local machine (i.e. when working on your own plugin)
" Plugin 'file:///home/gmarik/path/to/plugin'
" " The sparkup vim script is in a subdirectory of this repo called vim.
" " Pass the path to set the runtimepath properly.
" Plugin 'rstacruz/sparkup', {'rtp': 'vim/'}
"
" " All of your Plugins must be added before the following line


Plugin 'vim-ruby/vim-ruby'

Plugin 'vim-scripts/Conque-GDB'

Plugin 'airblade/vim-gitgutter'

Plugin 'moll/vim-node'

Plugin 'scrooloose/nerdtree'

Plugin 'Valloric/YouCompleteMe'

Plugin 'marijnh/tern_for_vim'

Plugin 'Raimondi/delimitMate'

Plugin 'jelera/vim-javascript-syntax'

Plugin 'nathanaelkane/vim-indent-guides'

Plugin 'therubymug/vim-pyte'

Plugin 'scrooloose/syntastic'

Plugin 'walm/jshint.vim'

Plugin 'scrooloose/nerdcommenter'

Plugin 'SirVer/ultisnips'

Plugin 'honza/vim-snippets'

Plugin 'yegappan/greplace'

let g:UltiSnipsExpandTrigger="<tab>"
let g:UltiSnipsJumpForwardTrigger="<c-p>"
let g:UltiSnipsJumpBackwardTrigger="<c-v>"

call vundle#end()            " required
filetype plugin indent on    " required


" " To ignore plugin indent changes, instead use:
" "filetype plugin on
" "
" " Brief help
" " :PluginList       - lists configured plugins
" " :PluginInstall    - installs plugins; append `!` to update or just
" :PluginUpdate
" " :PluginSearch foo - searches for foo; append `!` to refresh local cache
" " :PluginClean      - confirms removal of unused plugins; append `!` to
" auto-approve removal
" "
" " see :h vundle for more details or wiki for FAQ
" " Put your non-Plugin stuff after this line



"============================================================================
" Make :help appear in a full-screen tab, instead of a window
"============================================================================

"Only apply to .txt files...
augroup HelpInTabs
  autocmd!
  autocmd BufEnter  *.txt   call HelpInNewTab()
augroup END

"Only apply to help files...
function! HelpInNewTab ()
  if &buftype == 'help'
    "Convert the help window to a tab...
    execute "normal \<C-W>T"
  endif
endfunction


let mapleader=","

nnoremap / /\v

set ignorecase
set incsearch
set hlsearch

nnoremap q :set nohlsearch!<CR>

nmap aa :q!<CR>
nmap tt :w<CR>
nmap ta :wq<CR>

nnoremap <C-j> i

nnoremap w :bp<CR>
nnoremap r :bn<CR>

nnoremap f :wincmd W<CR>
nnoremap s :wincmd w<CR>

vmap t y
noremap t yy

nnoremap e <C-r>
nnoremap l N

nnoremap y :vs

vmap h <Plug>NERDCommenterToggle
nmap h <Plug>NERDCommenterToggle

noremap k gg=G

nnoremap nt :NERDTreeToggle<CR>

set nocompatible
syntax enable
filetype on
filetype plugin on

set clipboard=unnamedplus


"delimitMate configs

let delimitMate_expand_cr = 2
let delimitMate_expand_space = 1 

set background=light


set tabstop=2

"" Removes trailing spaces
function! TrimWhiteSpace()
   %s/\s\+$//e
endfunction

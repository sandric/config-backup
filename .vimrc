set rtp+=~/.vim/bundle/Vundle.vim

highlight LineNr ctermfg=grey
hi visual ctermbg=81

let mapleader=","

set nocompatible
set shell=/bin/bash
set expandtab
set shiftwidth=2
set softtabstop=2
set ignorecase
set incsearch
set hlsearch
set hidden
set clipboard=unnamedplus
set background=light
set tabstop=2
set backspace=2
set number
set smartindent
set cursorline
set wildmenu
set showmatch
set list
set listchars=tab:→\ ,trail:☮

call vundle#begin()

Plugin 'gmarik/Vundle.vim'

Plugin 'tpope/vim-fugitive'

Plugin 'git://git.wincent.com/command-t.git'

Plugin 'vim-ruby/vim-ruby'

Plugin 'vim-scripts/Conque-GDB'

Plugin 'airblade/vim-gitgutter'

Plugin 'moll/vim-node'

Plugin 'scrooloose/nerdtree'

Plugin 'Valloric/YouCompleteMe'

Plugin 'marijnh/tern_for_vim'

Plugin 'jelera/vim-javascript-syntax'

Plugin 'nathanaelkane/vim-indent-guides'

Plugin 'scrooloose/syntastic'

Plugin 'walm/jshint.vim'

Plugin 'scrooloose/nerdcommenter'

Plugin 'SirVer/ultisnips'

Plugin 'honza/vim-snippets'

Plugin 'yegappan/greplace'

Plugin 'nsf/gocode', {'rtp': 'vim/'}

Plugin 'ekalinin/Dockerfile.vim'

Plugin 'raimondi/delimitmate'

Plugin 'Lokaltog/vim-easymotion'

Plugin 'osyo-manga/vim-over'

Plugin 'digitaltoad/vim-jade'

Plugin 'kien/ctrlp.vim'

Plugin 'bling/vim-airline'

Plugin 'ntpeters/vim-better-whitespace'

Plugin 'sjl/badwolf'

Plugin 'rking/ag.vim'


let g:UltiSnipsExpandTrigger="<c-a>"
let g:UltiSnipsJumpForwardTrigger="<c-t>"
let g:UltiSnipsJumpBackwardTrigger="<c-r>"

let delimitMate_expand_cr = 2
let delimitMate_expand_space = 1

autocmd FileType ruby,eruby let g:rubycomplete_buffer_loading = 1
autocmd FileType ruby,eruby let g:rubycomplete_classes_in_global = 1
autocmd FileType ruby,eruby let g:rubycomplete_rails = 1

autocmd FileType javascript setlocal omnifunc=tern#Complete

let g:ycm_key_invoke_completion = '<c-t>'

let g:ctrlp_map = '<c-g>'
let g:ctrlp_cmd = 'CtrlP'

let g:ctrlp_match_window = 'bottom,order:ttb'
let g:ctrlp_switch_buffer = 0
let g:ctrlp_working_path_mode = 0
let g:ctrlp_user_command = 'ag %s -l --nocolor --hidden -g ""'


let g:airline_powerline_fonts = 1
set laststatus=2
let g:airline#extensions#tabline#enabled = 1

let g:agprg="/usr/bin/ag"

call vundle#end()


au BufRead,BufNewFile * start

syntax enable

filetype plugin indent on

colo badwolf


"Basic Remappings
nnoremap <C-o> <Esc><Esc>:
nnoremap <C-q> <Esc><Esc>

inoremap <C-a> <Esc><C-a><C-a>

"Saving/Closing
nmap a :bd<CR>
nmap t :w<CR>
nmap q :q!<CR>

"Window/Buffer manipulation
inoremap <C-u> <Esc>:wincmd h<CR>i
inoremap <C-e> <Esc>:wincmd l<CR>i
inoremap <C-n> <Esc>:bp<CR>i
inoremap <C-j> <Esc>:bn<CR>i
inoremap <C-l> <Esc>:vertical res +5<CR>i
inoremap <C-y> <Esc>:vertical res -5<CR>i
inoremap <C-p> <C-o>p

nnoremap <C-n> <Esc>:wincmd h<CR>i
nnoremap <C-j> <Esc>:wincmd l<CR>i
nnoremap <C-u> <Esc>:bp<CR>i
nnoremap <C-e> <Esc>:bn<CR>i
nnoremap <C-l> <Esc>:vertical res +5<CR>i
nnoremap <C-y> <Esc>:vertical res -5<CR>i
inoremap <C-p> <C-o>p

"Visual Mode
inoremap <C-t> <C-o>v
nnoremap <C-t> v
vnoremap <C-t> y
vnoremap <C-f> <End><Esc><Esc>v<Home>yi<End>
vnoremap <C-s> iwyi<End>
vnoremap <C-o> <Esc><Esc>
"vnoremap : <Esc><Esc>
vnoremap ( d
vnoremap = d
vnoremap b iB
vnoremap [ iBy
vnoremap i <Esc>
vnoremap <C-z> <gv
vnoremap <C-x> >gv
vnoremap <C-b> :OverCommandLine<CR>s/
vnoremap / y/<C-R>"<CR>"

"Command mode
cnoremap <C-o> <C-c>i
cnoremap <C-d> <C-c>i


"Searching
inoremap <C-k> <C-o>/
inoremap <C-b> <C-o>:OverCommandLine<CR>s/
inoremap <C-z> <C-o>N
inoremap <C-x> <C-o>n

nnoremap <C-k> /
nnoremap <C-b> :OverCommandLine<CR>s/
nnoremap <C-z> N
nnoremap <C-x> n

"Deleting
inoremap <C-s> <C-o>"_daw
inoremap <C-f> <C-o>dd

nnoremap <C-s> "_daw
nnoremap <C-f> dd

"Undo-Redo
inoremap <C-w> <C-o>u
inoremap <C-r> <C-o><C-r>

nnoremap <C-w> <C-o>u
nnoremap <C-r> <C-o><C-r>


"Plugins
"NerdCommenter
imap '' <C-o><Plug>NERDCommenterToggle
vmap <C-h> <Plug>NERDCommenterToggle
vmap ' <Plug>NERDCommenterToggle
vmap " <Plug>NERDCommenterToggle

"EasyMotion
let g:EasyMotion_smartcase = 1
imap <C-q> <C-o><Plug>(easymotion-s2)

"NerdTree
nnoremap nt :NERDTreeToggle<CR>

"CtrlP
inoremap <C-g> <Esc><C-g>

"Ag
inoremap <C-d> <Esc>:Ag 
nnoremap <C-d> <Esc>:Ag 
vnoremap <C-d> y<C-o>:Ag <C-R>"t

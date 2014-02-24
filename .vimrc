call pathogen#incubate()
call pathogen#helptags()

imap ii <C-[>

set number
:highlight LineNr ctermfg=darkgrey
set expandtab
set softtabstop=4
set tabstop=4
set shiftwidth=4

:command WQ wq
:command Wq wq
:command W w
:command Q q

set mouse=r

syntax enable
"set background=dark
"colorscheme solarized

nore ; :
nore , ;

" set backupdir=~/.vimbackups

"-------------------------------------
" Config for  vundle
"-------------------------------------

set nocompatible               " be iMproved
filetype on                   " required!

"set rtp+=~/.vim/bundle/vundle/
"call vundle#rc()

" let Vundle manage Vundle
" required 
"Bundle 'gmarik/vundle'

" My Bundles here:
"
" original repos on github
" Snipmate install dependencies:
"Bundle "MarcWeber/vim-addon-mw-utils"
"Bundle "tomtom/tlib_vim"
"Bundle "honza/snipmate-snippets"
"Bundle "garbas/vim-snipmate"

"Bundle "Raimondi/delimitMate"
" vim-scripts repos
"Bundle "c.vim"
"Bundle "a.vim"
"Bundle "Syntastic"
" non github repos

" 
autocmd FileType c,cpp set commentstring=//\ %s

" file specific flags
filetype plugin indent on     " required!

" Unite Mappings
nnoremap <C-p> :Unite file_rec/async<cr>
nnoremap <space>/ :Unite grep:.<cr>

" Paste in vim without autoindent
set pastetoggle=<F2>

" Sane searching
set hlsearch " Hilight search term
set showmatch " Show matching brackets
set incsearch " ... dynamically as they are typed"

"
" more at https://github.com/csexton/dotfiles/blob/master/home/vimrc#L381
"

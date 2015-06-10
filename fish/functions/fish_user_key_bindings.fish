function fish_user_key_bindings
  bind \cf backward-word
  #bind \cs custom_remove_word
  bind -M insert \cs forward-char forward-char backward-word kill-word
end

function custom_remove_word
  #commandline -f backward-word
  commandline -f forward-char
  commandline -f forward-char
  commandline -f backward-word
  #commandline -f kill-word
end

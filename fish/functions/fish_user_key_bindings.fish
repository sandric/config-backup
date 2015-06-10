function fish_user_key_bindings
  bind \cf custom_kill_line
  bind \cs custom_kill_word
end

function custom_kill_line
  commandline -f backward-kill-line
  commandline -f end-of-line
end

function custom_kill_word
  commandline -f kill-word
  commandline -f backward-word
  commandline -f forward-char
  commandline -f forward-char
end

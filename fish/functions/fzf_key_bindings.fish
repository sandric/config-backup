# Key bindings
# ------------
function fzf_key_bindings

  # Due to a bug of fish, we cannot use command substitution,
  # so we use temporary file instead
  if [ -z "$TMPDIR" ]
    set -g TMPDIR /tmp
  end

  function __fzf_escape
    while read item
      echo -n (echo -n "$item" | sed -E 's/([ "$~'\''([{<>})])/\\\\\\1/g')' '
    end
  end

  function __fzf_ctrl_t

    if test (commandline) = 'v '
      set is_with_command_prefix 1
    end

    set current_dir $PWD
    if test $current_dir = /
      set current_dir_length 2
    else
      set current_dir_length (expr length $PWD + 2)
    end
    command find $current_dir \( -path '/run' -o -path '/dev' -o -path '/var' -o -path '/sys' -o -fstype 'dev' -o -fstype 'proc' -o ! -readable \) -prune \
      -o -type f -print \
      -o -type d -print | sed 1d | cut -c$current_dir_length- | fzf > $TMPDIR/fzf.result

    and commandline -i (cat $TMPDIR/fzf.result | __fzf_escape)
    commandline -f repaint
    rm -f $TMPDIR/fzf.result

    if test $is_with_command_prefix
      #set -x history (commandline) $history
      eval (commandline)
      commandline -r ''
    end
  end

  function __fzf_ctrl_r
    history | eval (__fzfcmd) +s +m --tiebreak=index --toggle-sort=ctrl-r > $TMPDIR/fzf.result
    and commandline (cat $TMPDIR/fzf.result)
    commandline -f repaint
    rm -f $TMPDIR/fzf.result
  end

  function __fzf_alt_c
    command find -L . \( -path '*/\.*' -o -fstype 'dev' -o -fstype 'proc' \) \
      -prune -o -type d -print 2> /dev/null | sed 1d | cut -b3- | eval (__fzfcmd) +m > $TMPDIR/fzf.result
    [ (cat $TMPDIR/fzf.result | wc -l) -gt 0 ]
    and cd (cat $TMPDIR/fzf.result)
    commandline -f repaint
    rm -f $TMPDIR/fzf.result
  end

  function __fzfcmd
    #set -q FZF_TMUX; or set FZF_TMUX 1

    #if [ $FZF_TMUX -eq 1 ]
      #if set -q FZF_TMUX_HEIGHT
        #echo "fzf-tmux -d$FZF_TMUX_HEIGHT"
      #else
        #echo "fzf-tmux -d40%"
      #end
    #else
      echo "fzf"
    #end
  end

  bind \ca '__fzf_ctrl_t'
  #bind \cr '__fzf_ctrl_r'
  #bind \ec '__fzf_alt_c'

  #if bind -M insert > /dev/null 2>&1
    #bind -M insert \ct '__fzf_ctrl_t'
    #bind -M insert \cr '__fzf_ctrl_r'
    #bind -M insert \ec '__fzf_alt_c'
  #end
end


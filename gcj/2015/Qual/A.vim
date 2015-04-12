" Usage: vim -u NONE --noplugin -N -S A.vim -c SolveA A.in

function! s:solve(shynesses)
  let l:ans = 0
  let l:acc = 0
  let l:i = 0
  for l:shyness in a:shynesses
    if l:acc < l:i
      let l:diff = l:i - l:acc
      let l:ans += l:diff
      let l:acc += l:diff
    endif
    let l:acc += l:shyness
    let l:i += 1
  endfor
  return l:ans
endfunction

function! s:main()
  let l:t = str2nr(getline('.'))
  normal! j
  let l:i = 0
  let l:outputs = []

  while l:i < l:t
    let l:line = getline('.')
    normal! j
    let l:i += 1

    let l:shynesses = map(split(split(l:line)[1], '\zs'), 'str2nr(v:val)')
    call add(l:outputs, printf('Case #%d: %d', l:i, s:solve(l:shynesses)))
  endwhile

  edit %:r.out
  call setline('.', l:outputs)
  exit
endfunction

command! -nargs=0 SolveA call s:main()

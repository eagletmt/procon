" Usage: vim -u NONE --noplugin -N -S A.vim -c SolveA A.in

let s:cur_lnum = 1
function! s:readline()
  let l:line = getline(s:cur_lnum)
  let s:cur_lnum += 1
  return l:line
endfunction

function! s:readgrid()
  let l:grid = []
  for _ in range(4)
    let l:line = s:readline()
    call add(l:grid, map(split(l:line, '\s\+'), 'str2nr(v:val)'))
  endfor
  return l:grid
endfunction

function! s:main()
  let l:t = str2nr(s:readline())
  let l:i = 0
  let l:outputs = []
  while l:i < l:t
    let l:i += 1
    let l:ans1 = str2nr(s:readline())
    let l:grid1 = s:readgrid()
    let l:cand1 = l:grid1[l:ans1-1]
    let l:ans2 = str2nr(s:readline())
    let l:grid2 = s:readgrid()
    let l:cand2 = l:grid2[l:ans2-1]

    let l:cand = []
    for l:c1 in l:cand1
      for l:c2 in l:cand2
        if l:c1 == l:c2
          call add(l:cand, l:c1)
        endif
      endfor
    endfor
    call uniq(sort(l:cand))
    let l:len = len(l:cand)
    if l:len == 0
      call add(l:outputs, 'Volunteer cheated!')
    elseif l:len == 1
      call add(l:outputs, l:cand[0])
    else
      call add(l:outputs, 'Bad magician!')
    endif
  endwhile

  edit %:r.out
  let l:i = 0
  while l:i < l:t
    call setline(l:i+1, printf('Case #%d: %s', l:i+1, l:outputs[l:i]))
    let l:i += 1
  endwhile
  exit
endfunction

command! -nargs=0 SolveA call s:main()

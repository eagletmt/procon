#!/usr/bin/env ruby
t = $stdin.gets.to_i

1.upto(t) do |ti|
  r, t = *$stdin.gets.split(/ /).map(&:to_i)

  lo = 1
  hi = 1 << 100
  while lo < hi
    n = (lo + hi + 1)/2
    s = 2*n*n - n + 2*r*n
    if s <= t
      lo = n
    else
      hi = n-1
    end
  end
  puts "Case ##{ti}: #{lo}"
end

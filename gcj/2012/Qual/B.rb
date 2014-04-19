#!/usr/bin/ruby
require 'pp'

def solve(n, s, p, ts)
  ans = 0
  x = p+2*[p-1, 0].max
  ans += ts.count { |t| t >= x }
  ts.delete_if { |t| t >= x }
  y = p+2*[p-2, 0].max
  c = ts.count { |t| t >= y }
  ans += [c, s].min
  ans
end

t = $stdin.gets.to_i
t.times do |c|
  xs = $stdin.gets.chomp.split.map(&:to_i)
  puts "Case ##{c+1}: #{solve xs[0], xs[1], xs[2], xs[3 .. xs.size-1]}"
end

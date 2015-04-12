#!/usr/bin/env ruby

def solve2(ps, max_p)
  m = 0
  ps.each do |p|
    if p > max_p
      q, r = p.divmod(max_p)
      m += q - 1
      if r != 0
        m += 1
      end
    end
  end
  m + max_p
end

def solve(ps)
  max_p = ps.max
  ans = max_p
  1.upto(max_p) do |p|
    ans = [ans, solve2(ps, p)].min
  end
  ans
end

t = ARGF.gets.chomp.to_i
t.times do |i|
  ARGF.gets
  ps = ARGF.gets.chomp.split.map(&:to_i)
  puts "Case ##{i+1}: #{solve(ps)}"
end

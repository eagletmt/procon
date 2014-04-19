#!/usr/bin/ruby
require 'net/http'
require 'json'

if ARGV.empty?
  puts "usage: #{$0} contest_id"
  exit 1
end
contest_id = ARGV[0].to_i
N = 25

BASE_PATH = '/codejam/contest/scoreboard/do'
Net::HTTP.start('code.google.com') do |http|
  1.step(15000, N) do |pos|
    q = {
      :cmd => 'GetScoreboard',
      :contest_id => contest_id,
      :show_type => 'all',
      :start_pos => pos,
    }.map { |k, v| "#{k}=#{v}" }.join('&')
    res = http.get(BASE_PATH + '?' + q)
    if res.code.to_i != 200
      p res
      exit 1
    end

    rows = JSON.parse(res.body)['rows']
    rows.each do |row|
      rank = row['r']
      name = row['n']
      country = row['c']
      score = row['pts']
      times = row['ss']
      attempts = row['att']

      printf '%4d  %3d', rank, score
      times.zip(attempts) do |t, a|
        if t == -1
          print '  --:--:--'
        else
          printf '  %02d:%02d:%02d', t/60/60, (t/60)%60, t%60
        end
        print "(#{a})"
      end
      puts "  #{name} (#{country})"
    end

    if rows.size < N
      break
    end
  end
end

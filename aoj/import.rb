#!/usr/bin/env ruby
require 'net/http'
require 'time'
require 'pathname'
require 'nokogiri'

user = 'eagletmt'

EXT_MAP = {
  'C' => 'c',
  'C++' => 'cc',
  'JAVA' => 'java',
}

Net::HTTP.start('judge.u-aizu.ac.jp') do |http|
  body = http.get("/onlinejudge/webservice/source_manage?mode=problem&target=#{user}").body
  Nokogiri::XML.parse(body).xpath('//problem').map do |problem|
    id = problem.at_xpath('problem_id').inner_text
    doc2 = Nokogiri::XML.parse(http.get("/onlinejudge/webservice/source_manage?mode=submission&problemID=#{id}&target=#{user}").body)
    target = doc2.xpath('//submission').map do |submission|
      status = submission.at_xpath('status').inner_text
      if status == 'Accepted'
        {
          judge_id: submission.at_xpath('judge_id').inner_text,
          time: Time.parse(submission.at_xpath('submission_date').inner_text),
          language: submission.at_xpath('language').inner_text,
        }
      end
    end.compact.max_by { |sub| sub[:time] }
    if target
      path = Pathname.new("#{id.to_i / 1000}/#{target[:language] == 'JAVA' ? 'j' : ''}#{id}.#{EXT_MAP[target[:language]]}")
      puts "#{id} #{target[:judge_id]} -> #{path}"
      doc3 = Nokogiri::HTML.parse(http.get("/onlinejudge/review.jsp?rid=#{target[:judge_id]}").body)
      path.parent.mkpath
      path.open('w') do |f|
        f.puts doc3.at_css('#code').inner_text.gsub(/\n*\z/, '')
      end
    end
  end
end

fail "Please provide a summary in the Merge Request description to help your colleagues to understand the MR purpose." if gitlab.mr_body.length < 5

if git.modified_files.include? "Dangerfile"
  warn "This MR modifies Dangerfile! Watch for the rules!"
end

# Checking MR size
if not gitlab.mr_body.include?("#huge-sorry")
  warn("Split the MR into separate ones. It's really big.") if git.lines_of_code > 3000
  fail("Do not submit MRs over 5000 lines of code.") if git.lines_of_code > 5000
end

# Note when MRs don't reference a milestone, make the warning stick around on subsequent runs
has_milestone = gitlab.mr_json["milestone"] != nil
warn("This MR does not refer to an existing milestone", sticky: true) unless has_milestone

# check commits' comments
commit_lint.check warn: :all

# check gitlab issue in commit message
git.commits.each do |c|
  m = c.message.match(/^\[\#(\d+)\]\ (.*)/)
  if not m
    warn "No GitLab issue in commit message: #{c}"
    gl_issue_msg = nil
  else
    gl_issue_msg = m.captures[0]
  end

  mr_branch = gitlab.branch_for_head
  m = mr_branch.match(/^(\d+).*/)
  if not m
    warn "Branch name does not start with GitLab issue: #{mr_branch}"
    gl_issue_br = nil
  else
    gl_issue_br = m.captures[0]
  end

  if gl_issue_msg and gl_issue_br and gl_issue_msg != gl_issue_br
    warn "GitLab issue ##{gl_issue_msg} in msg of commit #{c} and issue ##{gl_issue_br} from branch #{mr_branch} do not match"
  end
end

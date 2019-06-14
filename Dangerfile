# Make it more obvious that a PR is a work in progress and shouldn't be merged yet
warn "MR is classed as Work in Progress" if gitlab.mr_title.include? "WIP"

fail "Please provide a summary in the Merge Request description to help your colleagues to understand the MR purpose." if gitlab.mr_body.length < 5

if git.modified_files.include? "Dangerfile"
  warn "This MR modifies Dangerfile! Watch for the rules!"
end

# Checking MR size
warn("Split the MR into separate ones. It's really big.") if git.lines_of_code > 400
fail("Do not submit MRs over 1000 lines of code.") if git.lines_of_code > 1000

# Note when MRs don't reference a milestone, make the warning stick around on subsequent runs
has_milestone = gitlab.mr_json["milestone"] != nil
warn("This MR does not refer to an existing milestone", sticky: true) unless has_milestone

# check commits' comments
commit_lint.check

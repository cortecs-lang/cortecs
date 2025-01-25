import re
from datetime import datetime
import git
import subprocess



print("Fetching bazelisk releases")
release_command = ['gh', 'release', 'list', '--repo', "https://github.com/bazelbuild/bazelisk"]
release_output = subprocess.run(release_command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
releases = release_output.stdout.decode("utf-8")
print("Releases stdout:", releases)
print("Releases stderr:", release_output.stderr.decode("utf-8"))
if release_output.returncode != 0:
    print("Failed to fetch bazelisk releases")
    exit(1)


latest = releases.splitlines()[0]
print("Latest release line:", latest)

assert latest.split()[1] == "Latest", "Failed to sanity check the release line. Fail CI the run"

latest_tag = latest.split()[2] 
print("Latest release:", latest_tag)

with open('.bazelw/bazelisk-version', 'r') as file:
    current_version = file.read().strip()

print("Current bazelisk version:", current_version)

if current_version == latest_tag:
    print("Bazelisk is up to date.")
    exit(0)

download_command = ["gh", "release", "download", latest_tag, "--clobber"]
download_command.extend(["--repo", "https://github.com/bazelbuild/bazelisk"])
download_command.extend(["--dir", ".bazelw"])
download_command.extend(["-p", "bazelisk-linux-*"])
download_command.extend(["-p", "bazelisk-darwin-*"])
download_command.extend(["-p", "bazelisk-windows-*"])

download_output = subprocess.run(download_command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
print("Download stdout:", download_output.stdout.decode("utf-8"))
print("Download stderr:", download_output.stderr.decode("utf-8"))
if download_output.returncode != 0:
    print("Failed to download bazelisk releases")
    exit(1)

with open('.bazelw/bazelisk-version', 'w') as file:
    file.write(latest_tag)

# Get most recent commit
repo = git.Repo()
main = repo.heads.main

# create new branch for the bazelisk update
new_branch = repo.create_head("update-bazelisk", main.commit)
new_branch.checkout()

# create the new commit for the bazelisk update
message = "chore(deps): Updating bazelisk to {}".format(latest_tag)
print("creating commit:", message)
index = repo.index
index.add([".bazelw/*"])
index.commit(message)

# push to new branch
today = datetime.now().strftime('%Y-%m-%d')
remote_branch_name = "dependency-update/bazelisk-{}".format(today)
print("pushing to new branch:", remote_branch_name)
branch_refspec = "HEAD:{}".format(remote_branch_name)
repo.remotes.origin.push(refspec=branch_refspec)

# create the PR
print("creating pull request")
pr_link = subprocess.check_output(['gh', 'pr', 'create', '--title', message, '--body', 'Automatic PR for dependency update.', '--base', 'main', '--head', remote_branch_name]).decode("utf-8")
print(pr_link)

for line in pr_link.splitlines():
    # Find the line with the PR number
    if "https://github.com/cortecs-lang/cortecs/pull/" in line:
        numbers = re.findall(r'\d+', line)
        if len(numbers) != 1:
            print("Found too many numbers in PR line number")
        else:
            # Get the PR number
            pr_num = numbers[0]
            print("Found PR number:", pr_num)
            # Comment on the PR to initiate a merge
            print("Kicking off automerge")
            subprocess.run(['gh', 'pr', 'merge', pr_num, '--merge', '--auto'])

# reset back to main branch
main.checkout()
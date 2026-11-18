# Week 1: Linux basics and Git

**Wednesday, 2026-11-18, 18:30–20:00 (HKT; 90 minutes)** · [ASC Team organization](https://github.com/hkust-asc)

Practice navigating a Linux server, separating program output, keeping a session alive, and submitting work through Git. See [training server access](#training-server-access) for the hostname and first connection.

Member-only guides: [WSL setup](https://github.com/hkust-asc/.github-private/blob/main/docs/wsl-setup.md) · [SSH and VS Code](https://github.com/hkust-asc/.github-private/blob/main/docs/ssh-vscode.md) · [Git rules](https://github.com/hkust-asc/.github-private/blob/main/docs/git-rules.md)

## Training server access

The training server hostname is `asc26.nooobkevin.fyi`, on port `22`. Accounts are handed out during the class session. For example, connect with:

```bash
ssh asc01@asc26.nooobkevin.fyi
```

Use the account handed to you. Before accepting a host key on your first connection, check that its fingerprint matches the corresponding key type below. These fingerprints were verified against the training server's host keys on 2026-11-18:

- ED25519: `SHA256:1h5mUMKSzLHP7dCxNImO9dID1qafnwPhveP9R2X8qa4`
- ECDSA: `SHA256:yXTPNfi1doCXsESbPcuTsIUdjBD5gfH/YdJ/IJoV+Ng`
- RSA: `SHA256:jWkxDx7zDQMx2aBu+KUoSyMuJ1hEnlfJCVerUe0UpU8`

## Beginner tutorials

These are general tutorials, not login instructions for the training server:

- [HPC Documentation](https://hkust-hpc-docs.readthedocs.io/latest/)
- [Linux](https://hkust-hpc-docs.readthedocs.io/latest/kb/linux/index.html)
- [Git and GitHub](https://hkust-hpc-docs.readthedocs.io/latest/kb/git/index.html)
- [How to Make a Pull Request](https://hkust-hpc-docs.readthedocs.io/latest/kb/git/how-to-make-a-pull-request.html)

## Quest 1: Connect and explore

1. Connect to the training server using your class account. See [training server access](#training-server-access) for the hostname, command, and host key fingerprints.
2. Create and enter your workspace:

   ```bash
   mkdir -p ~/workspace
   cd ~/workspace
   ```

3. Install `ranger` in your home directory without `sudo`, and set up an alias for Bash:

   ```bash
   git clone https://github.com/ranger/ranger.git ~/.ranger
   echo "alias ranger='python3 ~/.ranger/ranger.py'" >> ~/.bashrc
   source ~/.bashrc
   ```

4. Run `ranger /opt/asc_quest/` to explore the directory. Use the arrow keys to navigate and `q` to quit.

## Quest 2: Redirect output and use tmux

The coach will put `noisy_sensor.sh` and `long_sim.sh` on the server in `/opt/asc_quest/`. They are not stored in Git.

1. From `~/workspace`, run the sensor with standard output and standard error sent to separate files. The passcode line in `passcode.txt` should be clean, without error messages; errors should go to `error.log`. Then inspect both files:

   ```bash
   cd ~/workspace
   cat passcode.txt
   cat error.log
   ```

   <details>
   <summary>Hint: redirect the sensor output</summary>

   ```bash
   /opt/asc_quest/noisy_sensor.sh > passcode.txt 2> error.log
   ```

   </details>

   Keep the passcode for your profile.
2. Start a session named `sim` and run the simulation inside it:

   ```bash
   tmux new -s sim
   /opt/asc_quest/long_sim.sh
   ```

3. While it runs, press **Ctrl+B**, release both keys, then press **D** to detach. Reconnect to the server if you disconnected, and reattach:

   ```bash
   tmux attach -t sim
   ```

4. Once the simulation finishes, recover the Token from `~/sim_result.txt`:

   ```bash
   cat ~/sim_result.txt
   ```

## Quest 3: Submit a profile

You may use the server, local WSL/macOS/Linux, or VS Code Remote-SSH. If the server is not open yet, submit your profile first and add the Quest 2 results later.

1. Configure your Git identity and authenticate with GitHub in the environment you choose. Replace the placeholders with your preferred name and GitHub email:

   ```bash
   git config --global user.name "Your Preferred Name"
   git config --global user.email "your-github-email@example.com"
   gh auth login
   ```

   In the login prompts, choose **GitHub.com → HTTPS → login with a web browser**.
2. If you have not been added to `hkust-asc` or do not have write access to this repository, first use **Fork** on GitHub to create your own copy. Pushing directly to `origin` when it points to the organization repository will fail with a 403 without write access.

   Clone your fork and make your submission branch, replacing `YOUR_GITHUB_ID` with your GitHub ID:

   ```bash
   git clone https://github.com/YOUR_GITHUB_ID/ws26-01-linux-git.git
   cd ws26-01-linux-git
   git switch -c submit/YOUR_GITHUB_ID
   mkdir -p submissions/YOUR_GITHUB_ID
   ```

   If you already cloned the organization repository, run these commands inside your existing clone instead:

   ```bash
   git remote add fork https://github.com/YOUR_GITHUB_ID/ws26-01-linux-git.git
   git switch -c submit/YOUR_GITHUB_ID
   mkdir -p submissions/YOUR_GITHUB_ID
   ```

   Then use `fork` instead of `origin` in the push command below. If you have write access, you may clone and push to the organization repository instead.
3. Create `submissions/YOUR_GITHUB_ID/profile.md` with your preferred name or nickname, year and major, the Quest 2 passcode and Token when available, and one or two HPC interests. Do not include a student ID or legal full name in your profile or PR title.
4. Stage your profile, commit it with a descriptive message, and push your branch to your fork (or to the organization repository if you have write access):

   ```bash
   git add submissions/YOUR_GITHUB_ID/profile.md
   git commit -m "Add workshop profile"
   git push -u origin submit/YOUR_GITHUB_ID
   ```

5. On GitHub, open a pull request from your fork's `submit/<github-id>` branch into `hkust-asc/ws26-01-linux-git` on `main`, titled `[Submit] Preferred Name (@github-id)`. If you pushed directly to the organization repository, open the PR from your branch there instead.

## Quest 4: Bonus bug report

Inspect `quests/matmul_buggy.c` and identify the bug. Do not push a fix to `main`. Open an issue titled `[Bug] matmul_buggy.c: short description` explaining the problem and your proposed fix.

## Working rules

- Use `submit/<github-id>` for assignments and `fix/<github-id>-<short-description>` for fixes. Do not push to `main`.
- Unless a quest requires editing a shared file, work only under `submissions/<github-id>/`; do not edit the originals in `quests/` or another person's folder.
- Make commit messages describe the change. `update`, `111`, and `asdf` are not allowed.
- Use `[Submit] Preferred Name (@github-id)` for submission PRs, and `[Bug] filename: short description` or `[Question] description of the problem` for issues. Never put a student ID or legal full name in a profile or PR title.
- Check `git status` before committing. Do not add generated artifacts, logs, datasets, or model weights.

`slides/` and `demos/` hold workshop materials; `quests/` holds exercise files; `submissions/` holds individual work.

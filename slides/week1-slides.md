---
marp: true
theme: default
paginate: true
---

# Week 1: Linux, SSH & Git Survival Guide
**ASC Team**
Wednesday, 2026-11-18

---

## Today's Roadmap (90 mins)

1. **Part 1: Linux CLI & Session Survival** *(15 mins)*
   - Navigating without a GUI (`pwd`, `ls`, `cd`, `mkdir`, `touch`)
   - Streams & Redirection (`stdin`, `stdout`, `stderr`)
   - Keeping tasks alive (`tmux`)
2. **Part 2: HPC Architecture & Git Workflow** *(15 mins)*
   - Local PC vs. Remote Server vs. HPC Cluster
   - Git & GitHub Collaboration (`branch` -> `commit` -> `push` -> `PR`)
   - VS Code Remote-SSH + GitHub Copilot Setup
3. **Hands-on Quests 1–4** *(60 mins)*

---

## 1. Where Are Commands Running? (HPC Mental Model)

```text
[ Your Laptop ]              [ Shared Server / HPC Cluster ]
 Windows (WSL)  --- SSH --->  Login Node (輕量編輯、編譯、發任務)
 or macOS                      │
                               ├──(Slurm Scheduler: sbatch / squeue)
                               ▼
                              Compute Nodes (CPU / GPU 真正跑大算力的裸機)
```

- **Why Linux CLI?** Supercomputers have **no GUI**. Everything is controlled via SSH.
- **`tmux` vs. `Slurm`**：
  - Single test server (today): Use **`tmux`** so tasks survive Wi-Fi drops.
  - Real HPC cluster (later): **NEVER** run heavy jobs in `tmux` on the Login Node! Use **Slurm** to dispatch jobs to Compute Nodes.

---

## 2. Minimal `vim` Survival Kit (Don't Panic!)

When Git or Linux drops you into `vim`, remember **2 modes**:

1. **Normal Mode** (Default when opened — keys are commands, NOT typing!)
2. **Insert Mode** (Press **`i`** to start typing text like Notepad)

**How to escape & save:**
- Press **`Esc`** (back to Normal Mode)
- Type **`:wq`** + `Enter` $\rightarrow$ **W**rite (save) & **Q**uit
- Type **`:q!`** + `Enter` $\rightarrow$ **Q**uit WITHOUT saving (emergency exit!)

*(Tip: You can also use `nano filename` or VS Code Remote-SSH!)*

---

## 3. Git & GitHub Mental Model

Why not send `code_final_v3_real.zip` on WhatsApp?

```text
Working Directory  --(git add)-->  Staging Area  --(git commit)-->  Local Branch
                                                                         │
GitHub Main Repo  <--(Pull Request)--  Remote Branch  <--(git push)──────┘
```

- **Never push directly to `main`!**
- Always create your own branch: `git switch -c submit/<your-id>`
- **Pull Request (PR)** = Asking the team to review & merge your branch.
- **Issue** = Reporting a bug, proposing a topic, or asking a question.

---

## 4. Modern Tooling: VS Code + AI

- **VS Code `Remote - SSH`**: Edit remote Linux files smoothly as if they were local.
- **GitHub Student Developer Pack**:
  - Apply with your `@connect.ust.hk` email!
  - Unlocks **GitHub Copilot** (inline completions + chat to explain complex C/Fortran/MPI code).
- ⚠️ **Server Courtesy**: Today 30+ people share one VM — avoid installing heavy extensions on the remote host if using SSH terminal works for you.

---

## 🚀 Time for Hands-on! (60 mins)

Open **`github.com/hkust-asc/ws26-01-linux-git`**

- **Quest 1**: SSH into the training server & install `ranger` without `sudo`
- **Quest 2**: Separate `stdout`/`stderr` + survive a disconnect with `tmux`
- **Quest 3**: Create a branch, add `submissions/<id>/profile.md`, and open a **PR**! *(Watch the big screen as PRs come in!)*
- **Quest 4 (Bonus)**: Use AI/eyes to find the bug in `quests/matmul_buggy.c` & open an **Issue**

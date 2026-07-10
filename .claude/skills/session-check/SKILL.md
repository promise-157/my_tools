---
name: Session Check
description: |
  监控会话上下文健康和项目文件状态。启动会话时加载一次，指令常驻上下文，后续每次回复自动附加状态行。
  Monitor session context health and project file state. Load once at session start; instructions persist across turns to prepend context status to every response.
when_to_use: |
  当用户提出涉及代码、文件、修改、项目任务的请求时触发——覆盖大部分工程对话。
  用户说"改一下xxx"、"这个文件"、"帮我写"、"看看代码"、"提交"等时自动加载。
  纯闲聊、关于 Claude 自身的提问、不涉及文件的纯概念讨论时跳过。
  Trigger when the user asks about code, files, modifications, or project tasks —
  this covers most engineering conversations. Skip for pure chat, questions about
  yourself (Claude), or conceptual discussions without file involvement.
---

# Session Status Monitor

Once loaded, prepend a **one-line status block** to every response that involves
code, files, or project work. Skip it for casual conversation.

## Status Line Format

```
📊 上下文[health] | 余量[remaining] | 🌿 [branch] | 📝 [files]
```

## Field Definitions

### health — context confusion level

Judge by scanning the conversation:

| Signal | Assessment |
|--------|------------|
| Clean conversation, ≤30 turns, no compaction summary visible | **无混淆** |
| 1 compaction has occurred, or 30-50 turns | **轻度混淆** |
| ≥2 compactions, 50+ turns, or you catch yourself re-asking / losing earlier details | **⚠️ 建议重启** |

When health is **⚠️ 建议重启**, append to the status line:
`— 建议 /clear 或新开对话`

### remaining — context capacity estimate

Estimate qualitatively from conversation length and compaction count:

| Condition | Label |
|-----------|-------|
| ≤15 turns, 0 compactions | **余量充足** |
| 15-35 turns, ≤1 compaction | **余量适中** |
| 35-50 turns, 1-2 compactions | **余量偏少** |
| 50+ turns, ≥2 compactions | **余量不足** |

### branch

Run before responding:
```bash
git branch --show-current 2>/dev/null || echo "non-repo"
```

### files — changed files summary

Run before responding:
```bash
git status --short 2>/dev/null
```

Condense to: `N files` (count of lines), or `clean` if empty, or omit entirely if not a git repo.
When there are ≤3 changed files, list their names inline. Over 3 files, show the count.

## Examples

```
📊 上下文无混淆 | 余量充足 | 🌿 main | 📝 i2c.cpp, i2c.h

[开始回答用户问题...]
```

```
📊 上下文无混淆 | 余量适中 | 🌿 main | 📝 5 files

[开始回答...]
```

```
📊 上下文⚠️建议重启 | 余量不足 | 🌿 feat/new-api | 📝 3 files — 建议 /clear 或新开对话

[开始回答...]
```

## Notes

- Keep it **one line**, no taller — it's a prefix, not a report.
- Run `git status --short` and `git branch --show-current` each time you respond;
  they're instant and give live data.
- If you're not in a git repo, drop the 🌿 and 📝 fields — only show context health.
- When compaction drops this skill from context, the status line will stop appearing.
  The user should re-invoke `/session-check` to restore it.

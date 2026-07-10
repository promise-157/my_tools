---
name: list-skills.md
description: 查看所有可用的 Claude Code Skills。当用户询问"有哪些skills"、"查看skills"、"skills列表"、"什么技能可用"、"列出所有技能"时触发，动态扫描并分类展示。
---

# Skills 列表查看器

当用户询问技能列表时，**动态扫描**以下位置并分类展示结果。

## 扫描步骤

### 1. 项目本地 Skills
```bash
ls -1 .claude/skills/ 2>/dev/null
```
读取每个 `.md` 文件 frontmatter 中的 `description` 字段。

### 2. 用户级 Skills
```bash
ls -1 ~/.claude/skills/ 2>/dev/null
```
读取每个 `.md` 文件 frontmatter 中的 `description` 字段。

### 3. 内置 Skills
从当前会话的 `<system-reminder>` 中提取 `available_skills` 列表。

---

## 输出格式

```
📊 Skills 完整列表
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

📂 项目本地 Skills (N个) — .claude/skills/
  • skill-name — 描述

👤 用户级 Skills (N个) — ~/.claude/skills/
  • skill-name — 描述

⚡ 内置 Skills (N个)
  • skill-name — 描述

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
总计: N 个技能
```

## 注意事项

- 每次都执行实际扫描，不要硬编码列表
- 用户级目录可能不存在，需用 `2>/dev/null` 处理
- 优先展示 skill 文件 frontmatter 中的 `description`

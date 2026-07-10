# my_tools

嵌入式 C++ 小工具集合，每个工具是独立模块。

## 项目结构

```
src/modules/<name>/    # 工具模块 (name.h + name.cpp)
src/examples/<name>/   # 对应模块的使用示例 (main.cpp)
src/3rdparty/          # 第三方库 (git submodule)
```

- 新增工具时在 `src/modules/` 和 `src/examples/` 下各建一个同名文件夹
- 模块间依赖用相对路径 include，如 `#include "../delay/delay.h"`
- 无统一构建系统，每个 example 单独编译

## 编码风格

- C++ 头文件用 `#ifndef NAME_H` / `#define NAME_H` / `#endif // NAME_H`
- 固定宽度类型用 `<stdint.h>`（uint8_t、uint32_t 等）
- 功能复杂的模块用类封装（如 I2C），简单的用自由函数（如 delay）
- 源文件头注释保留作者信息



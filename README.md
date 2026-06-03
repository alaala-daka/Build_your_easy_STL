# The-process-of-self-building-STL-is-outlined-herewith.
Building STL step by step to get familiar to Data Structure.
# The-process-of-self-building-STL-is-outlined-herewith.

本项目旨在通过从零手写常用数据结构和算法，深入理解 C++ STL 的设计思想与底层实现。以下按顺序列出已实现的核心组件及其特性。

## 数据结构实现

### 1. Vector
动态数组，支持随机访问和自动扩容。  
- **实现要点**：连续内存、三倍或两倍增长策略、RAII 管理。  
- **核心接口**：`push_back`、`pop_back`、`operator[]`、`size`/`capacity`、迭代器支持。

### 2. Linked List
双向循环链表，非连续存储，高效插入/删除。  
- **实现要点**：带哨兵节点的双向链接、节点动态分配。  
- **核心接口**：`push_front`/`push_back`、`pop_front`/`pop_back`、`insert`/`erase`、双向迭代器。

### 3. Stack
后进先出（LIFO）容器适配器，默认基于 `Vector` 实现。  
- **实现要点**：封装底层容器，仅提供栈顶操作。  
- **核心接口**：`push`、`pop`、`top`、`empty`、`size`。

### 4. Queue
先进先出（FIFO）容器适配器，默认基于 `Linked List` 实现。  
- **实现要点**：避免 `Vector` 的低效头部删除，使用链表或循环数组。  
- **核心接口**：`push`、`pop`、`front`、`back`、`empty`、`size`。

### 5. Consistent Hashing
一致性哈希环，用于分布式缓存或负载均衡。  
- **实现要点**：哈希环 + 虚拟节点，支持节点动态增删时最小化数据迁移。  
- **核心接口**：`addNode`、`removeNode`、`getNode(key)`、虚拟节点数量可配置。

### 6. BST (Binary Search Tree)
非平衡二叉搜索树，基础数据结构。  
- **实现要点**：左小右大递归定义、中序遍历有序。  
- **核心接口**：`insert`、`search`、`remove`（合并或复制删除法）、遍历（前/中/后序）。

### 7. AVL (Adelson-Velsky and Landis Tree)
自平衡二叉搜索树，严格维护平衡因子。  
- **实现要点**：节点高度跟踪、四种旋转（LL/RR/LR/RL）、插入/删除后回溯调整。  
- **核心接口**：`insert`、`erase`、`find`、`isBalanced` 验证。

### 8. RBT (Red-Black Tree)
红黑树，近似平衡的二叉搜索树，C++ STL `map`/`set` 的经典底层实现。  
- **实现要点**：节点红黑性质（根黑、红子黑、黑高一致）、插入/删除时的颜色修复与旋转。  
- **核心接口**：`insert`、`erase`、`find`、`lower_bound`/`upper_bound`、迭代器顺序遍历。

---

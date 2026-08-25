#include <list>
#include <unordered_map>
#include <optional>
#include <iterator>

using BlockId = int;

class MemoryManager {
    struct Block {
        int left;
        int right;
        bool free = true;
    };

public:
    explicit MemoryManager(int size): blocks_{{0, size, true}} {}

    std::optional<BlockId> acquire(int size) {
        auto it = blocks_.begin();
        
        for (;it != blocks_.end(); ++it) {
            if (!it->free || (it->right - it->left) < size) {
                continue;
            }
                
            if ((it->right - it->left) == size) {
                it->free = false;
                used_[nextBlockId_] = it;

                return nextBlockId_++;
            }
            
            auto new_it = blocks_.insert(it, {it->left, it->left + size, false});
            it->left += size;

            used_[nextBlockId_] = new_it;

            return nextBlockId_++;
        }

        return std::nullopt;
    }

    void release(BlockId blockId) {
        auto it = used_.find(blockId);
        if (it == used_.end()) {
            return;
        }

        auto list_it = it->second;

        used_.erase(blockId);

        list_it->free = true;

        if (list_it != blocks_.begin()) {
            auto prev_it = std::prev(list_it);
            if (prev_it->free) {
                list_it->left = prev_it->left;
                blocks_.erase(prev_it);
            }
        }

        auto next_it = std::next(list_it);
        if (next_it != blocks_.end() && next_it->free) {
            list_it->right = next_it->right;
            blocks_.erase(next_it);
        }
    }

private:
    std::list<Block> blocks_;
    std::unordered_map<BlockId, std::list<Block>::iterator> used_;
    BlockId nextBlockId_ = 0;
};
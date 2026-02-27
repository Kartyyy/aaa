#include "huffman.hh"
#include <unordered_map>
#include <string>

std::unique_ptr<Node> buildHuffmanTree(const std::string& message)
{
    if (message.empty())
        return nullptr;

    std::unordered_map<char, float> frequencies;

    for (const char c : message)
        frequencies[c]++;

    PriorityQueue queue;

    for (const auto& [symbol, weight] : frequencies)
        queue.push(std::make_unique<Node>(weight, symbol));

    if (queue.size() == 1)
        return queue.pop();

    while (queue.size() > 1)
    {
        auto left = queue.pop();
        auto right = queue.pop();

        auto parent = std::make_unique<Node>(
            left->weight + right->weight,
            std::move(left),
            std::move(right)
        );

        queue.push(std::move(parent));
    }

    return queue.pop();
}

static void buildCodeRecursive(
    const std::unique_ptr<Node>& node,
    const std::string& prefix,
    std::unordered_map<char, std::string>& table)
{
    if (!node)
        return;

    if (node->symbol.has_value())
    {
        table[node->symbol.value()] =
            prefix.empty() ? "0" : prefix;
        return;
    }

    buildCodeRecursive(node->left, prefix + "0", table);
    buildCodeRecursive(node->right, prefix + "1", table);
}

std::unordered_map<char, std::string>
buildCodeTable(const std::unique_ptr<Node>& root)
{
    std::unordered_map<char, std::string> table;

    buildCodeRecursive(root, "", table);

    return table;
}

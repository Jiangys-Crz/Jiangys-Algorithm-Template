// 先准备字符串 s 和分隔符 sep。保留空字段。

for (size_t l = 0; ; ) {
    auto r = s.find(sep, l);
    auto field = s.substr(l, r == string::npos ? r : r - l);
    // 待填写：处理当前字段 field，包含空字段。
    if (r == string::npos) break;
    l = r + 1;
}

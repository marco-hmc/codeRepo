import os


def generate_summary(directory):
    summary = "# Summary\n\n"

    for root, dirs, files in os.walk(directory):
        level = root.replace(directory, "").count(os.sep)
        indent = "  " * level
        summary += f"{indent}* [{os.path.basename(root)}/]({root}/)\n"
        sub_indent = "  " * (level + 1)
        for file in files:
            if file.endswith(".md") and file != "README.md":
                summary += f"{sub_indent}* [{file[:-3]}]({os.path.join(root, file)})\n"

    with open("summary.md", "w") as f:
        f.write(summary)


# 指定你的代码仓库目录
directory = (
    r"C:\Users\marco\Documents\1_codeRepo\codeRepoProject\codeRepo\99_tmp\testMd"
)
generate_summary(directory)

import os
import subprocess

def batch_git_clone(repo_list, target_dir):
    if not os.path.exists(target_dir):
        os.makedirs(target_dir)
    
    for repo in repo_list:
        repo_name = repo.split('/')[-1].replace('.git', '')
        repo_path = os.path.join(target_dir, repo_name)
        
        if not os.path.exists(repo_path):
            subprocess.run(['git', 'clone', repo, repo_path])
        else:
            print(f"Repository {repo_name} already exists at {repo_path}")

# Example usage
repositories = [
    'https://github.com/user/repo1.git',
    'https://github.com/user/repo2.git',
    'https://github.com/user/repo3.git'
]

target_directory = '/path/to/clone/repositories'

batch_git_clone(repositories, target_directory)
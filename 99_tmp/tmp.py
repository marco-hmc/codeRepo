import asyncio

async def task1():
    print("Task 1 started")
    await asyncio.sleep(5)  # 非阻塞等待5秒
    print("Task 1 finished")

async def task2():
    print("Task 2 started")
    await asyncio.sleep(2)  # 非阻塞等待2秒
    print("Task 2 finished")

async def main():
    await asyncio.gather(task1(), task2())  # 并发执行task1和task2

# 运行主协程
asyncio.run(main())
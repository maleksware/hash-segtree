import os
from alive_progress import alive_bar
import time

def run_tests(program_name, test_type):
    num_tests_to_run = 10 ** 6
    step = 10000

    with alive_bar(num_tests_to_run // step, title=f"{program_name} on {test_type}") as bar:
        with open(f"{program_name}.csv", "a") as fout_csv:
            for i in range(step, num_tests_to_run + 1, step):
                for j in range(3):
                    with open("dump.out", "w") as f:
                        f.write("") # clear the output file

                    start_time = time.time()
                    os.system(f"build\\{program_name}.exe {test_type} < tests\\{test_type}\\test{i}_{j}.in > dump.out")
                    end_time = time.time()

                    delta_time_ms = (end_time - start_time) * 1000

                    fout_csv.write(f"{test_type},{i},{delta_time_ms}\n")
                bar()

# run_tests("hash", "qp")

# run_tests("hash", "ln")

# run_tests("point", "qp")

# run_tests("point", "ln")

# run_tests("range", "qp")

# run_tests("range", "ln")


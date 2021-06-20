use employees;
EXPLAIN SELECT dept_name, title, COUNT(DISTINCT T.emp_no)
FROM titles T, departments D, dept_emp DE
WHERE T.emp_no=DE.emp_no and D.dept_no=DE.dept_no
GROUP BY D.dept_no, title
ORDER BY D.dept_no, title

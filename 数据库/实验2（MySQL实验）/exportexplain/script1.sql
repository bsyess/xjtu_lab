use employees;
EXPLAIN SELECT D.dept_no, D.dept_name, COUNT(*), MIN(salary), AVG(salary), MAX(salary), SUM(salary)
FROM departments D, employees E, salaries S, dept_emp DE
WHERE D.dept_no=DE.dept_no and E.emp_no=S.emp_no and E.emp_no=DE.emp_no
GROUP BY D.dept_no;

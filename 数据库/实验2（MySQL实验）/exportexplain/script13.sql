use employees;
EXPLAIN SELECT E.emp_no, CONCAT(first_name, ' ',last_name)
FROM employees E
WHERE NOT EXISTS(
SELECT *
FROM departments D
WHERE NOT EXISTS(
SELECT *
FROM dept_emp DE
WHERE DE.dept_no=D.dept_no and E.emp_no=DE.emp_no
))


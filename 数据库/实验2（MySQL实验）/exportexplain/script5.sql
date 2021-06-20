use employees;
EXPLAIN SELECT E.emp_no, CONCAT(first_name, ' ',last_name), COUNT(*)
FROM employees E, dept_emp DE
WHERE E.emp_no=DE.emp_no 
GROUP BY emp_no

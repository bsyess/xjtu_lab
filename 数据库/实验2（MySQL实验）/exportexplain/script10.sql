use employees;
EXPLAIN SELECT E.emp_no, CONCAT(first_name, ' ',last_name)
FROM employees E
WHERE E.emp_no IN(
SELECT DISTINCT emp_no
FROM dept_manager DM)
ORDER BY E.emp_no

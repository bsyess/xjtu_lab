use employees;
EXPLAIN SELECT E.emp_no, CONCAT(first_name, ' ',last_name), from_date, to_date, title
FROM employees E, titles T
WHERE E.emp_no=T.emp_no
ORDER BY E.emp_no, from_date


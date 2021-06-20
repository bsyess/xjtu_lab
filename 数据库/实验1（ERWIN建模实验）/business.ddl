
CREATE TABLE 仓库
( 
	仓库号               integer  NOT NULL ,
	仓库名               varchar(20)  NULL ,
	地址                 varchar(20)  NULL 
)
go



ALTER TABLE 仓库
	ADD CONSTRAINT XPK仓库 PRIMARY KEY  CLUSTERED (仓库号 ASC)
go



CREATE TABLE 供应
( 
	商店号               integer  NOT NULL ,
	商品号               varchar(20)  NOT NULL ,
	仓库号               integer  NOT NULL ,
	月供应量             char(18)  NULL ,
	月份                 char(18)  NULL 
)
go



ALTER TABLE 供应
	ADD CONSTRAINT XPK供应 PRIMARY KEY  CLUSTERED (商店号 ASC,商品号 ASC,仓库号 ASC)
go



CREATE TABLE 库存
( 
	仓库号               integer  NOT NULL ,
	商品号               varchar(20)  NOT NULL ,
	日期                 char(18)  NULL ,
	存储量               char(18)  NULL 
)
go



ALTER TABLE 库存
	ADD CONSTRAINT XPK库存 PRIMARY KEY  CLUSTERED (仓库号 ASC,商品号 ASC)
go



CREATE TABLE 商店
( 
	商店号               integer  NOT NULL ,
	商店名               varchar(20)  NULL ,
	地址                 varchar(20)  NULL 
)
go



ALTER TABLE 商店
	ADD CONSTRAINT XPK商店 PRIMARY KEY  CLUSTERED (商店号 ASC)
go



CREATE TABLE 商品
( 
	商品号               varchar(20)  NOT NULL ,
	商品名               varchar(20)  NULL ,
	单价                 integer  NULL 
)
go



ALTER TABLE 商品
	ADD CONSTRAINT XPK商品 PRIMARY KEY  CLUSTERED (商品号 ASC)
go



CREATE TABLE 销售
( 
	商店号               integer  NOT NULL ,
	商品号               varchar(20)  NOT NULL ,
	月份                 char(18)  NULL ,
	月销售量             char(18)  NULL 
)
go



ALTER TABLE 销售
	ADD CONSTRAINT XPK销售 PRIMARY KEY  CLUSTERED (商店号 ASC,商品号 ASC)
go




ALTER TABLE 供应
	ADD CONSTRAINT R_38 FOREIGN KEY (商店号) REFERENCES 商店(商店号)
		ON DELETE NO ACTION
		ON UPDATE NO ACTION
go




ALTER TABLE 供应
	ADD CONSTRAINT R_40 FOREIGN KEY (商品号) REFERENCES 商品(商品号)
		ON DELETE NO ACTION
		ON UPDATE NO ACTION
go




ALTER TABLE 供应
	ADD CONSTRAINT R_42 FOREIGN KEY (仓库号) REFERENCES 仓库(仓库号)
		ON DELETE NO ACTION
		ON UPDATE NO ACTION
go




ALTER TABLE 库存
	ADD CONSTRAINT R_25 FOREIGN KEY (仓库号) REFERENCES 仓库(仓库号)
		ON DELETE NO ACTION
		ON UPDATE NO ACTION
go




ALTER TABLE 库存
	ADD CONSTRAINT R_30 FOREIGN KEY (商品号) REFERENCES 商品(商品号)
		ON DELETE NO ACTION
		ON UPDATE NO ACTION
go




ALTER TABLE 销售
	ADD CONSTRAINT R_27 FOREIGN KEY (商店号) REFERENCES 商店(商店号)
		ON DELETE NO ACTION
		ON UPDATE NO ACTION
go




ALTER TABLE 销售
	ADD CONSTRAINT R_32 FOREIGN KEY (商品号) REFERENCES 商品(商品号)
		ON DELETE NO ACTION
		ON UPDATE NO ACTION
go




CREATE TRIGGER tD_仓库 ON 仓库 FOR DELETE AS
/* ERwin Builtin Trigger */
/* DELETE trigger on 仓库 */
BEGIN
  DECLARE  @errno   int,
           @errmsg  varchar(255)
    /* ERwin Builtin Trigger */
    /* 仓库  库存 on parent delete no action */
    /* ERWIN_RELATION:CHECKSUM="0001a0bf", PARENT_OWNER="", PARENT_TABLE="仓库"
    CHILD_OWNER="", CHILD_TABLE="库存"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_25", FK_COLUMNS="仓库号" */
    IF EXISTS (
      SELECT * FROM deleted,库存
      WHERE
        /*  %JoinFKPK(库存,deleted," = "," AND") */
        库存.仓库号 = deleted.仓库号
    )
    BEGIN
      SELECT @errno  = 30001,
             @errmsg = 'Cannot delete 仓库 because 库存 exists.'
      GOTO ERROR
    END

    /* ERwin Builtin Trigger */
    /* 仓库  供应 on parent delete no action */
    /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="仓库"
    CHILD_OWNER="", CHILD_TABLE="供应"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_42", FK_COLUMNS="仓库号" */
    IF EXISTS (
      SELECT * FROM deleted,供应
      WHERE
        /*  %JoinFKPK(供应,deleted," = "," AND") */
        供应.仓库号 = deleted.仓库号
    )
    BEGIN
      SELECT @errno  = 30001,
             @errmsg = 'Cannot delete 仓库 because 供应 exists.'
      GOTO ERROR
    END


    /* ERwin Builtin Trigger */
    RETURN
ERROR:
    raiserror @errno @errmsg
    rollback transaction
END

go


CREATE TRIGGER tU_仓库 ON 仓库 FOR UPDATE AS
/* ERwin Builtin Trigger */
/* UPDATE trigger on 仓库 */
BEGIN
  DECLARE  @NUMROWS int,
           @nullcnt int,
           @validcnt int,
           @ins仓库号 integer,
           @errno   int,
           @errmsg  varchar(255)

  SELECT @NUMROWS = @@rowcount
  /* ERwin Builtin Trigger */
  /* 仓库  库存 on parent update no action */
  /* ERWIN_RELATION:CHECKSUM="0001d403", PARENT_OWNER="", PARENT_TABLE="仓库"
    CHILD_OWNER="", CHILD_TABLE="库存"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_25", FK_COLUMNS="仓库号" */
  IF
    /* %ParentPK(" OR",UPDATE) */
    UPDATE(仓库号)
  BEGIN
    IF EXISTS (
      SELECT * FROM deleted,库存
      WHERE
        /*  %JoinFKPK(库存,deleted," = "," AND") */
        库存.仓库号 = deleted.仓库号
    )
    BEGIN
      SELECT @errno  = 30005,
             @errmsg = 'Cannot update 仓库 because 库存 exists.'
      GOTO ERROR
    END
  END

  /* ERwin Builtin Trigger */
  /* 仓库  供应 on parent update no action */
  /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="仓库"
    CHILD_OWNER="", CHILD_TABLE="供应"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_42", FK_COLUMNS="仓库号" */
  IF
    /* %ParentPK(" OR",UPDATE) */
    UPDATE(仓库号)
  BEGIN
    IF EXISTS (
      SELECT * FROM deleted,供应
      WHERE
        /*  %JoinFKPK(供应,deleted," = "," AND") */
        供应.仓库号 = deleted.仓库号
    )
    BEGIN
      SELECT @errno  = 30005,
             @errmsg = 'Cannot update 仓库 because 供应 exists.'
      GOTO ERROR
    END
  END


  /* ERwin Builtin Trigger */
  RETURN
ERROR:
    raiserror @errno @errmsg
    rollback transaction
END

go




CREATE TRIGGER tD_供应 ON 供应 FOR DELETE AS
/* ERwin Builtin Trigger */
/* DELETE trigger on 供应 */
BEGIN
  DECLARE  @errno   int,
           @errmsg  varchar(255)
    /* ERwin Builtin Trigger */
    /* 商店  供应 on child delete no action */
    /* ERWIN_RELATION:CHECKSUM="00030e84", PARENT_OWNER="", PARENT_TABLE="商店"
    CHILD_OWNER="", CHILD_TABLE="供应"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_38", FK_COLUMNS="商店号" */
    IF EXISTS (SELECT * FROM deleted,商店
      WHERE
        /* %JoinFKPK(deleted,商店," = "," AND") */
        deleted.商店号 = 商店.商店号 AND
        NOT EXISTS (
          SELECT * FROM 供应
          WHERE
            /* %JoinFKPK(供应,商店," = "," AND") */
            供应.商店号 = 商店.商店号
        )
    )
    BEGIN
      SELECT @errno  = 30010,
             @errmsg = 'Cannot delete last 供应 because 商店 exists.'
      GOTO ERROR
    END

    /* ERwin Builtin Trigger */
    /* 商品  供应 on child delete no action */
    /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="商品"
    CHILD_OWNER="", CHILD_TABLE="供应"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_40", FK_COLUMNS="商品号" */
    IF EXISTS (SELECT * FROM deleted,商品
      WHERE
        /* %JoinFKPK(deleted,商品," = "," AND") */
        deleted.商品号 = 商品.商品号 AND
        NOT EXISTS (
          SELECT * FROM 供应
          WHERE
            /* %JoinFKPK(供应,商品," = "," AND") */
            供应.商品号 = 商品.商品号
        )
    )
    BEGIN
      SELECT @errno  = 30010,
             @errmsg = 'Cannot delete last 供应 because 商品 exists.'
      GOTO ERROR
    END

    /* ERwin Builtin Trigger */
    /* 仓库  供应 on child delete no action */
    /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="仓库"
    CHILD_OWNER="", CHILD_TABLE="供应"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_42", FK_COLUMNS="仓库号" */
    IF EXISTS (SELECT * FROM deleted,仓库
      WHERE
        /* %JoinFKPK(deleted,仓库," = "," AND") */
        deleted.仓库号 = 仓库.仓库号 AND
        NOT EXISTS (
          SELECT * FROM 供应
          WHERE
            /* %JoinFKPK(供应,仓库," = "," AND") */
            供应.仓库号 = 仓库.仓库号
        )
    )
    BEGIN
      SELECT @errno  = 30010,
             @errmsg = 'Cannot delete last 供应 because 仓库 exists.'
      GOTO ERROR
    END


    /* ERwin Builtin Trigger */
    RETURN
ERROR:
    raiserror @errno @errmsg
    rollback transaction
END

go


CREATE TRIGGER tU_供应 ON 供应 FOR UPDATE AS
/* ERwin Builtin Trigger */
/* UPDATE trigger on 供应 */
BEGIN
  DECLARE  @NUMROWS int,
           @nullcnt int,
           @validcnt int,
           @ins商店号 integer, 
           @ins商品号 varchar(20), 
           @ins仓库号 integer,
           @errno   int,
           @errmsg  varchar(255)

  SELECT @NUMROWS = @@rowcount
  /* ERwin Builtin Trigger */
  /* 商店  供应 on child update no action */
  /* ERWIN_RELATION:CHECKSUM="00039284", PARENT_OWNER="", PARENT_TABLE="商店"
    CHILD_OWNER="", CHILD_TABLE="供应"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_38", FK_COLUMNS="商店号" */
  IF
    /* %ChildFK(" OR",UPDATE) */
    UPDATE(商店号)
  BEGIN
    SELECT @nullcnt = 0
    SELECT @validcnt = count(*)
      FROM inserted,商店
        WHERE
          /* %JoinFKPK(inserted,商店) */
          inserted.商店号 = 商店.商店号
    /* %NotnullFK(inserted," IS NULL","select @nullcnt = count(*) from inserted where"," AND") */
    
    IF @validcnt + @nullcnt != @NUMROWS
    BEGIN
      SELECT @errno  = 30007,
             @errmsg = 'Cannot update 供应 because 商店 does not exist.'
      GOTO ERROR
    END
  END

  /* ERwin Builtin Trigger */
  /* 商品  供应 on child update no action */
  /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="商品"
    CHILD_OWNER="", CHILD_TABLE="供应"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_40", FK_COLUMNS="商品号" */
  IF
    /* %ChildFK(" OR",UPDATE) */
    UPDATE(商品号)
  BEGIN
    SELECT @nullcnt = 0
    SELECT @validcnt = count(*)
      FROM inserted,商品
        WHERE
          /* %JoinFKPK(inserted,商品) */
          inserted.商品号 = 商品.商品号
    /* %NotnullFK(inserted," IS NULL","select @nullcnt = count(*) from inserted where"," AND") */
    
    IF @validcnt + @nullcnt != @NUMROWS
    BEGIN
      SELECT @errno  = 30007,
             @errmsg = 'Cannot update 供应 because 商品 does not exist.'
      GOTO ERROR
    END
  END

  /* ERwin Builtin Trigger */
  /* 仓库  供应 on child update no action */
  /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="仓库"
    CHILD_OWNER="", CHILD_TABLE="供应"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_42", FK_COLUMNS="仓库号" */
  IF
    /* %ChildFK(" OR",UPDATE) */
    UPDATE(仓库号)
  BEGIN
    SELECT @nullcnt = 0
    SELECT @validcnt = count(*)
      FROM inserted,仓库
        WHERE
          /* %JoinFKPK(inserted,仓库) */
          inserted.仓库号 = 仓库.仓库号
    /* %NotnullFK(inserted," IS NULL","select @nullcnt = count(*) from inserted where"," AND") */
    
    IF @validcnt + @nullcnt != @NUMROWS
    BEGIN
      SELECT @errno  = 30007,
             @errmsg = 'Cannot update 供应 because 仓库 does not exist.'
      GOTO ERROR
    END
  END


  /* ERwin Builtin Trigger */
  RETURN
ERROR:
    raiserror @errno @errmsg
    rollback transaction
END

go




CREATE TRIGGER tD_库存 ON 库存 FOR DELETE AS
/* ERwin Builtin Trigger */
/* DELETE trigger on 库存 */
BEGIN
  DECLARE  @errno   int,
           @errmsg  varchar(255)
    /* ERwin Builtin Trigger */
    /* 仓库  库存 on child delete no action */
    /* ERWIN_RELATION:CHECKSUM="0002051c", PARENT_OWNER="", PARENT_TABLE="仓库"
    CHILD_OWNER="", CHILD_TABLE="库存"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_25", FK_COLUMNS="仓库号" */
    IF EXISTS (SELECT * FROM deleted,仓库
      WHERE
        /* %JoinFKPK(deleted,仓库," = "," AND") */
        deleted.仓库号 = 仓库.仓库号 AND
        NOT EXISTS (
          SELECT * FROM 库存
          WHERE
            /* %JoinFKPK(库存,仓库," = "," AND") */
            库存.仓库号 = 仓库.仓库号
        )
    )
    BEGIN
      SELECT @errno  = 30010,
             @errmsg = 'Cannot delete last 库存 because 仓库 exists.'
      GOTO ERROR
    END

    /* ERwin Builtin Trigger */
    /* 商品  库存 on child delete no action */
    /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="商品"
    CHILD_OWNER="", CHILD_TABLE="库存"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_30", FK_COLUMNS="商品号" */
    IF EXISTS (SELECT * FROM deleted,商品
      WHERE
        /* %JoinFKPK(deleted,商品," = "," AND") */
        deleted.商品号 = 商品.商品号 AND
        NOT EXISTS (
          SELECT * FROM 库存
          WHERE
            /* %JoinFKPK(库存,商品," = "," AND") */
            库存.商品号 = 商品.商品号
        )
    )
    BEGIN
      SELECT @errno  = 30010,
             @errmsg = 'Cannot delete last 库存 because 商品 exists.'
      GOTO ERROR
    END


    /* ERwin Builtin Trigger */
    RETURN
ERROR:
    raiserror @errno @errmsg
    rollback transaction
END

go


CREATE TRIGGER tU_库存 ON 库存 FOR UPDATE AS
/* ERwin Builtin Trigger */
/* UPDATE trigger on 库存 */
BEGIN
  DECLARE  @NUMROWS int,
           @nullcnt int,
           @validcnt int,
           @ins仓库号 integer, 
           @ins商品号 varchar(20),
           @errno   int,
           @errmsg  varchar(255)

  SELECT @NUMROWS = @@rowcount
  /* ERwin Builtin Trigger */
  /* 仓库  库存 on child update no action */
  /* ERWIN_RELATION:CHECKSUM="000259df", PARENT_OWNER="", PARENT_TABLE="仓库"
    CHILD_OWNER="", CHILD_TABLE="库存"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_25", FK_COLUMNS="仓库号" */
  IF
    /* %ChildFK(" OR",UPDATE) */
    UPDATE(仓库号)
  BEGIN
    SELECT @nullcnt = 0
    SELECT @validcnt = count(*)
      FROM inserted,仓库
        WHERE
          /* %JoinFKPK(inserted,仓库) */
          inserted.仓库号 = 仓库.仓库号
    /* %NotnullFK(inserted," IS NULL","select @nullcnt = count(*) from inserted where"," AND") */
    
    IF @validcnt + @nullcnt != @NUMROWS
    BEGIN
      SELECT @errno  = 30007,
             @errmsg = 'Cannot update 库存 because 仓库 does not exist.'
      GOTO ERROR
    END
  END

  /* ERwin Builtin Trigger */
  /* 商品  库存 on child update no action */
  /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="商品"
    CHILD_OWNER="", CHILD_TABLE="库存"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_30", FK_COLUMNS="商品号" */
  IF
    /* %ChildFK(" OR",UPDATE) */
    UPDATE(商品号)
  BEGIN
    SELECT @nullcnt = 0
    SELECT @validcnt = count(*)
      FROM inserted,商品
        WHERE
          /* %JoinFKPK(inserted,商品) */
          inserted.商品号 = 商品.商品号
    /* %NotnullFK(inserted," IS NULL","select @nullcnt = count(*) from inserted where"," AND") */
    
    IF @validcnt + @nullcnt != @NUMROWS
    BEGIN
      SELECT @errno  = 30007,
             @errmsg = 'Cannot update 库存 because 商品 does not exist.'
      GOTO ERROR
    END
  END


  /* ERwin Builtin Trigger */
  RETURN
ERROR:
    raiserror @errno @errmsg
    rollback transaction
END

go




CREATE TRIGGER tD_商店 ON 商店 FOR DELETE AS
/* ERwin Builtin Trigger */
/* DELETE trigger on 商店 */
BEGIN
  DECLARE  @errno   int,
           @errmsg  varchar(255)
    /* ERwin Builtin Trigger */
    /* 商店  销售 on parent delete no action */
    /* ERWIN_RELATION:CHECKSUM="0001b95e", PARENT_OWNER="", PARENT_TABLE="商店"
    CHILD_OWNER="", CHILD_TABLE="销售"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_27", FK_COLUMNS="商店号" */
    IF EXISTS (
      SELECT * FROM deleted,销售
      WHERE
        /*  %JoinFKPK(销售,deleted," = "," AND") */
        销售.商店号 = deleted.商店号
    )
    BEGIN
      SELECT @errno  = 30001,
             @errmsg = 'Cannot delete 商店 because 销售 exists.'
      GOTO ERROR
    END

    /* ERwin Builtin Trigger */
    /* 商店  供应 on parent delete no action */
    /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="商店"
    CHILD_OWNER="", CHILD_TABLE="供应"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_38", FK_COLUMNS="商店号" */
    IF EXISTS (
      SELECT * FROM deleted,供应
      WHERE
        /*  %JoinFKPK(供应,deleted," = "," AND") */
        供应.商店号 = deleted.商店号
    )
    BEGIN
      SELECT @errno  = 30001,
             @errmsg = 'Cannot delete 商店 because 供应 exists.'
      GOTO ERROR
    END


    /* ERwin Builtin Trigger */
    RETURN
ERROR:
    raiserror @errno @errmsg
    rollback transaction
END

go


CREATE TRIGGER tU_商店 ON 商店 FOR UPDATE AS
/* ERwin Builtin Trigger */
/* UPDATE trigger on 商店 */
BEGIN
  DECLARE  @NUMROWS int,
           @nullcnt int,
           @validcnt int,
           @ins商店号 integer,
           @errno   int,
           @errmsg  varchar(255)

  SELECT @NUMROWS = @@rowcount
  /* ERwin Builtin Trigger */
  /* 商店  销售 on parent update no action */
  /* ERWIN_RELATION:CHECKSUM="0001df7b", PARENT_OWNER="", PARENT_TABLE="商店"
    CHILD_OWNER="", CHILD_TABLE="销售"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_27", FK_COLUMNS="商店号" */
  IF
    /* %ParentPK(" OR",UPDATE) */
    UPDATE(商店号)
  BEGIN
    IF EXISTS (
      SELECT * FROM deleted,销售
      WHERE
        /*  %JoinFKPK(销售,deleted," = "," AND") */
        销售.商店号 = deleted.商店号
    )
    BEGIN
      SELECT @errno  = 30005,
             @errmsg = 'Cannot update 商店 because 销售 exists.'
      GOTO ERROR
    END
  END

  /* ERwin Builtin Trigger */
  /* 商店  供应 on parent update no action */
  /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="商店"
    CHILD_OWNER="", CHILD_TABLE="供应"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_38", FK_COLUMNS="商店号" */
  IF
    /* %ParentPK(" OR",UPDATE) */
    UPDATE(商店号)
  BEGIN
    IF EXISTS (
      SELECT * FROM deleted,供应
      WHERE
        /*  %JoinFKPK(供应,deleted," = "," AND") */
        供应.商店号 = deleted.商店号
    )
    BEGIN
      SELECT @errno  = 30005,
             @errmsg = 'Cannot update 商店 because 供应 exists.'
      GOTO ERROR
    END
  END


  /* ERwin Builtin Trigger */
  RETURN
ERROR:
    raiserror @errno @errmsg
    rollback transaction
END

go




CREATE TRIGGER tD_商品 ON 商品 FOR DELETE AS
/* ERwin Builtin Trigger */
/* DELETE trigger on 商品 */
BEGIN
  DECLARE  @errno   int,
           @errmsg  varchar(255)
    /* ERwin Builtin Trigger */
    /* 商品  库存 on parent delete no action */
    /* ERWIN_RELATION:CHECKSUM="00027435", PARENT_OWNER="", PARENT_TABLE="商品"
    CHILD_OWNER="", CHILD_TABLE="库存"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_30", FK_COLUMNS="商品号" */
    IF EXISTS (
      SELECT * FROM deleted,库存
      WHERE
        /*  %JoinFKPK(库存,deleted," = "," AND") */
        库存.商品号 = deleted.商品号
    )
    BEGIN
      SELECT @errno  = 30001,
             @errmsg = 'Cannot delete 商品 because 库存 exists.'
      GOTO ERROR
    END

    /* ERwin Builtin Trigger */
    /* 商品  销售 on parent delete no action */
    /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="商品"
    CHILD_OWNER="", CHILD_TABLE="销售"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_32", FK_COLUMNS="商品号" */
    IF EXISTS (
      SELECT * FROM deleted,销售
      WHERE
        /*  %JoinFKPK(销售,deleted," = "," AND") */
        销售.商品号 = deleted.商品号
    )
    BEGIN
      SELECT @errno  = 30001,
             @errmsg = 'Cannot delete 商品 because 销售 exists.'
      GOTO ERROR
    END

    /* ERwin Builtin Trigger */
    /* 商品  供应 on parent delete no action */
    /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="商品"
    CHILD_OWNER="", CHILD_TABLE="供应"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_40", FK_COLUMNS="商品号" */
    IF EXISTS (
      SELECT * FROM deleted,供应
      WHERE
        /*  %JoinFKPK(供应,deleted," = "," AND") */
        供应.商品号 = deleted.商品号
    )
    BEGIN
      SELECT @errno  = 30001,
             @errmsg = 'Cannot delete 商品 because 供应 exists.'
      GOTO ERROR
    END


    /* ERwin Builtin Trigger */
    RETURN
ERROR:
    raiserror @errno @errmsg
    rollback transaction
END

go


CREATE TRIGGER tU_商品 ON 商品 FOR UPDATE AS
/* ERwin Builtin Trigger */
/* UPDATE trigger on 商品 */
BEGIN
  DECLARE  @NUMROWS int,
           @nullcnt int,
           @validcnt int,
           @ins商品号 varchar(20),
           @errno   int,
           @errmsg  varchar(255)

  SELECT @NUMROWS = @@rowcount
  /* ERwin Builtin Trigger */
  /* 商品  库存 on parent update no action */
  /* ERWIN_RELATION:CHECKSUM="0002e22f", PARENT_OWNER="", PARENT_TABLE="商品"
    CHILD_OWNER="", CHILD_TABLE="库存"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_30", FK_COLUMNS="商品号" */
  IF
    /* %ParentPK(" OR",UPDATE) */
    UPDATE(商品号)
  BEGIN
    IF EXISTS (
      SELECT * FROM deleted,库存
      WHERE
        /*  %JoinFKPK(库存,deleted," = "," AND") */
        库存.商品号 = deleted.商品号
    )
    BEGIN
      SELECT @errno  = 30005,
             @errmsg = 'Cannot update 商品 because 库存 exists.'
      GOTO ERROR
    END
  END

  /* ERwin Builtin Trigger */
  /* 商品  销售 on parent update no action */
  /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="商品"
    CHILD_OWNER="", CHILD_TABLE="销售"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_32", FK_COLUMNS="商品号" */
  IF
    /* %ParentPK(" OR",UPDATE) */
    UPDATE(商品号)
  BEGIN
    IF EXISTS (
      SELECT * FROM deleted,销售
      WHERE
        /*  %JoinFKPK(销售,deleted," = "," AND") */
        销售.商品号 = deleted.商品号
    )
    BEGIN
      SELECT @errno  = 30005,
             @errmsg = 'Cannot update 商品 because 销售 exists.'
      GOTO ERROR
    END
  END

  /* ERwin Builtin Trigger */
  /* 商品  供应 on parent update no action */
  /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="商品"
    CHILD_OWNER="", CHILD_TABLE="供应"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_40", FK_COLUMNS="商品号" */
  IF
    /* %ParentPK(" OR",UPDATE) */
    UPDATE(商品号)
  BEGIN
    IF EXISTS (
      SELECT * FROM deleted,供应
      WHERE
        /*  %JoinFKPK(供应,deleted," = "," AND") */
        供应.商品号 = deleted.商品号
    )
    BEGIN
      SELECT @errno  = 30005,
             @errmsg = 'Cannot update 商品 because 供应 exists.'
      GOTO ERROR
    END
  END


  /* ERwin Builtin Trigger */
  RETURN
ERROR:
    raiserror @errno @errmsg
    rollback transaction
END

go




CREATE TRIGGER tD_销售 ON 销售 FOR DELETE AS
/* ERwin Builtin Trigger */
/* DELETE trigger on 销售 */
BEGIN
  DECLARE  @errno   int,
           @errmsg  varchar(255)
    /* ERwin Builtin Trigger */
    /* 商店  销售 on child delete no action */
    /* ERWIN_RELATION:CHECKSUM="00020ce8", PARENT_OWNER="", PARENT_TABLE="商店"
    CHILD_OWNER="", CHILD_TABLE="销售"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_27", FK_COLUMNS="商店号" */
    IF EXISTS (SELECT * FROM deleted,商店
      WHERE
        /* %JoinFKPK(deleted,商店," = "," AND") */
        deleted.商店号 = 商店.商店号 AND
        NOT EXISTS (
          SELECT * FROM 销售
          WHERE
            /* %JoinFKPK(销售,商店," = "," AND") */
            销售.商店号 = 商店.商店号
        )
    )
    BEGIN
      SELECT @errno  = 30010,
             @errmsg = 'Cannot delete last 销售 because 商店 exists.'
      GOTO ERROR
    END

    /* ERwin Builtin Trigger */
    /* 商品  销售 on child delete no action */
    /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="商品"
    CHILD_OWNER="", CHILD_TABLE="销售"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_32", FK_COLUMNS="商品号" */
    IF EXISTS (SELECT * FROM deleted,商品
      WHERE
        /* %JoinFKPK(deleted,商品," = "," AND") */
        deleted.商品号 = 商品.商品号 AND
        NOT EXISTS (
          SELECT * FROM 销售
          WHERE
            /* %JoinFKPK(销售,商品," = "," AND") */
            销售.商品号 = 商品.商品号
        )
    )
    BEGIN
      SELECT @errno  = 30010,
             @errmsg = 'Cannot delete last 销售 because 商品 exists.'
      GOTO ERROR
    END


    /* ERwin Builtin Trigger */
    RETURN
ERROR:
    raiserror @errno @errmsg
    rollback transaction
END

go


CREATE TRIGGER tU_销售 ON 销售 FOR UPDATE AS
/* ERwin Builtin Trigger */
/* UPDATE trigger on 销售 */
BEGIN
  DECLARE  @NUMROWS int,
           @nullcnt int,
           @validcnt int,
           @ins商店号 integer, 
           @ins商品号 varchar(20),
           @errno   int,
           @errmsg  varchar(255)

  SELECT @NUMROWS = @@rowcount
  /* ERwin Builtin Trigger */
  /* 商店  销售 on child update no action */
  /* ERWIN_RELATION:CHECKSUM="00027877", PARENT_OWNER="", PARENT_TABLE="商店"
    CHILD_OWNER="", CHILD_TABLE="销售"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_27", FK_COLUMNS="商店号" */
  IF
    /* %ChildFK(" OR",UPDATE) */
    UPDATE(商店号)
  BEGIN
    SELECT @nullcnt = 0
    SELECT @validcnt = count(*)
      FROM inserted,商店
        WHERE
          /* %JoinFKPK(inserted,商店) */
          inserted.商店号 = 商店.商店号
    /* %NotnullFK(inserted," IS NULL","select @nullcnt = count(*) from inserted where"," AND") */
    
    IF @validcnt + @nullcnt != @NUMROWS
    BEGIN
      SELECT @errno  = 30007,
             @errmsg = 'Cannot update 销售 because 商店 does not exist.'
      GOTO ERROR
    END
  END

  /* ERwin Builtin Trigger */
  /* 商品  销售 on child update no action */
  /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="商品"
    CHILD_OWNER="", CHILD_TABLE="销售"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_32", FK_COLUMNS="商品号" */
  IF
    /* %ChildFK(" OR",UPDATE) */
    UPDATE(商品号)
  BEGIN
    SELECT @nullcnt = 0
    SELECT @validcnt = count(*)
      FROM inserted,商品
        WHERE
          /* %JoinFKPK(inserted,商品) */
          inserted.商品号 = 商品.商品号
    /* %NotnullFK(inserted," IS NULL","select @nullcnt = count(*) from inserted where"," AND") */
    
    IF @validcnt + @nullcnt != @NUMROWS
    BEGIN
      SELECT @errno  = 30007,
             @errmsg = 'Cannot update 销售 because 商品 does not exist.'
      GOTO ERROR
    END
  END


  /* ERwin Builtin Trigger */
  RETURN
ERROR:
    raiserror @errno @errmsg
    rollback transaction
END

go



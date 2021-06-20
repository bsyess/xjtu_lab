
CREATE TABLE �ֿ�
( 
	�ֿ��               integer  NOT NULL ,
	�ֿ���               varchar(20)  NULL ,
	��ַ                 varchar(20)  NULL 
)
go



ALTER TABLE �ֿ�
	ADD CONSTRAINT XPK�ֿ� PRIMARY KEY  CLUSTERED (�ֿ�� ASC)
go



CREATE TABLE ��Ӧ
( 
	�̵��               integer  NOT NULL ,
	��Ʒ��               varchar(20)  NOT NULL ,
	�ֿ��               integer  NOT NULL ,
	�¹�Ӧ��             char(18)  NULL ,
	�·�                 char(18)  NULL 
)
go



ALTER TABLE ��Ӧ
	ADD CONSTRAINT XPK��Ӧ PRIMARY KEY  CLUSTERED (�̵�� ASC,��Ʒ�� ASC,�ֿ�� ASC)
go



CREATE TABLE ���
( 
	�ֿ��               integer  NOT NULL ,
	��Ʒ��               varchar(20)  NOT NULL ,
	����                 char(18)  NULL ,
	�洢��               char(18)  NULL 
)
go



ALTER TABLE ���
	ADD CONSTRAINT XPK��� PRIMARY KEY  CLUSTERED (�ֿ�� ASC,��Ʒ�� ASC)
go



CREATE TABLE �̵�
( 
	�̵��               integer  NOT NULL ,
	�̵���               varchar(20)  NULL ,
	��ַ                 varchar(20)  NULL 
)
go



ALTER TABLE �̵�
	ADD CONSTRAINT XPK�̵� PRIMARY KEY  CLUSTERED (�̵�� ASC)
go



CREATE TABLE ��Ʒ
( 
	��Ʒ��               varchar(20)  NOT NULL ,
	��Ʒ��               varchar(20)  NULL ,
	����                 integer  NULL 
)
go



ALTER TABLE ��Ʒ
	ADD CONSTRAINT XPK��Ʒ PRIMARY KEY  CLUSTERED (��Ʒ�� ASC)
go



CREATE TABLE ����
( 
	�̵��               integer  NOT NULL ,
	��Ʒ��               varchar(20)  NOT NULL ,
	�·�                 char(18)  NULL ,
	��������             char(18)  NULL 
)
go



ALTER TABLE ����
	ADD CONSTRAINT XPK���� PRIMARY KEY  CLUSTERED (�̵�� ASC,��Ʒ�� ASC)
go




ALTER TABLE ��Ӧ
	ADD CONSTRAINT R_38 FOREIGN KEY (�̵��) REFERENCES �̵�(�̵��)
		ON DELETE NO ACTION
		ON UPDATE NO ACTION
go




ALTER TABLE ��Ӧ
	ADD CONSTRAINT R_40 FOREIGN KEY (��Ʒ��) REFERENCES ��Ʒ(��Ʒ��)
		ON DELETE NO ACTION
		ON UPDATE NO ACTION
go




ALTER TABLE ��Ӧ
	ADD CONSTRAINT R_42 FOREIGN KEY (�ֿ��) REFERENCES �ֿ�(�ֿ��)
		ON DELETE NO ACTION
		ON UPDATE NO ACTION
go




ALTER TABLE ���
	ADD CONSTRAINT R_25 FOREIGN KEY (�ֿ��) REFERENCES �ֿ�(�ֿ��)
		ON DELETE NO ACTION
		ON UPDATE NO ACTION
go




ALTER TABLE ���
	ADD CONSTRAINT R_30 FOREIGN KEY (��Ʒ��) REFERENCES ��Ʒ(��Ʒ��)
		ON DELETE NO ACTION
		ON UPDATE NO ACTION
go




ALTER TABLE ����
	ADD CONSTRAINT R_27 FOREIGN KEY (�̵��) REFERENCES �̵�(�̵��)
		ON DELETE NO ACTION
		ON UPDATE NO ACTION
go




ALTER TABLE ����
	ADD CONSTRAINT R_32 FOREIGN KEY (��Ʒ��) REFERENCES ��Ʒ(��Ʒ��)
		ON DELETE NO ACTION
		ON UPDATE NO ACTION
go




CREATE TRIGGER tD_�ֿ� ON �ֿ� FOR DELETE AS
/* ERwin Builtin Trigger */
/* DELETE trigger on �ֿ� */
BEGIN
  DECLARE  @errno   int,
           @errmsg  varchar(255)
    /* ERwin Builtin Trigger */
    /* �ֿ�  ��� on parent delete no action */
    /* ERWIN_RELATION:CHECKSUM="0001a0bf", PARENT_OWNER="", PARENT_TABLE="�ֿ�"
    CHILD_OWNER="", CHILD_TABLE="���"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_25", FK_COLUMNS="�ֿ��" */
    IF EXISTS (
      SELECT * FROM deleted,���
      WHERE
        /*  %JoinFKPK(���,deleted," = "," AND") */
        ���.�ֿ�� = deleted.�ֿ��
    )
    BEGIN
      SELECT @errno  = 30001,
             @errmsg = 'Cannot delete �ֿ� because ��� exists.'
      GOTO ERROR
    END

    /* ERwin Builtin Trigger */
    /* �ֿ�  ��Ӧ on parent delete no action */
    /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="�ֿ�"
    CHILD_OWNER="", CHILD_TABLE="��Ӧ"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_42", FK_COLUMNS="�ֿ��" */
    IF EXISTS (
      SELECT * FROM deleted,��Ӧ
      WHERE
        /*  %JoinFKPK(��Ӧ,deleted," = "," AND") */
        ��Ӧ.�ֿ�� = deleted.�ֿ��
    )
    BEGIN
      SELECT @errno  = 30001,
             @errmsg = 'Cannot delete �ֿ� because ��Ӧ exists.'
      GOTO ERROR
    END


    /* ERwin Builtin Trigger */
    RETURN
ERROR:
    raiserror @errno @errmsg
    rollback transaction
END

go


CREATE TRIGGER tU_�ֿ� ON �ֿ� FOR UPDATE AS
/* ERwin Builtin Trigger */
/* UPDATE trigger on �ֿ� */
BEGIN
  DECLARE  @NUMROWS int,
           @nullcnt int,
           @validcnt int,
           @ins�ֿ�� integer,
           @errno   int,
           @errmsg  varchar(255)

  SELECT @NUMROWS = @@rowcount
  /* ERwin Builtin Trigger */
  /* �ֿ�  ��� on parent update no action */
  /* ERWIN_RELATION:CHECKSUM="0001d403", PARENT_OWNER="", PARENT_TABLE="�ֿ�"
    CHILD_OWNER="", CHILD_TABLE="���"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_25", FK_COLUMNS="�ֿ��" */
  IF
    /* %ParentPK(" OR",UPDATE) */
    UPDATE(�ֿ��)
  BEGIN
    IF EXISTS (
      SELECT * FROM deleted,���
      WHERE
        /*  %JoinFKPK(���,deleted," = "," AND") */
        ���.�ֿ�� = deleted.�ֿ��
    )
    BEGIN
      SELECT @errno  = 30005,
             @errmsg = 'Cannot update �ֿ� because ��� exists.'
      GOTO ERROR
    END
  END

  /* ERwin Builtin Trigger */
  /* �ֿ�  ��Ӧ on parent update no action */
  /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="�ֿ�"
    CHILD_OWNER="", CHILD_TABLE="��Ӧ"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_42", FK_COLUMNS="�ֿ��" */
  IF
    /* %ParentPK(" OR",UPDATE) */
    UPDATE(�ֿ��)
  BEGIN
    IF EXISTS (
      SELECT * FROM deleted,��Ӧ
      WHERE
        /*  %JoinFKPK(��Ӧ,deleted," = "," AND") */
        ��Ӧ.�ֿ�� = deleted.�ֿ��
    )
    BEGIN
      SELECT @errno  = 30005,
             @errmsg = 'Cannot update �ֿ� because ��Ӧ exists.'
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




CREATE TRIGGER tD_��Ӧ ON ��Ӧ FOR DELETE AS
/* ERwin Builtin Trigger */
/* DELETE trigger on ��Ӧ */
BEGIN
  DECLARE  @errno   int,
           @errmsg  varchar(255)
    /* ERwin Builtin Trigger */
    /* �̵�  ��Ӧ on child delete no action */
    /* ERWIN_RELATION:CHECKSUM="00030e84", PARENT_OWNER="", PARENT_TABLE="�̵�"
    CHILD_OWNER="", CHILD_TABLE="��Ӧ"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_38", FK_COLUMNS="�̵��" */
    IF EXISTS (SELECT * FROM deleted,�̵�
      WHERE
        /* %JoinFKPK(deleted,�̵�," = "," AND") */
        deleted.�̵�� = �̵�.�̵�� AND
        NOT EXISTS (
          SELECT * FROM ��Ӧ
          WHERE
            /* %JoinFKPK(��Ӧ,�̵�," = "," AND") */
            ��Ӧ.�̵�� = �̵�.�̵��
        )
    )
    BEGIN
      SELECT @errno  = 30010,
             @errmsg = 'Cannot delete last ��Ӧ because �̵� exists.'
      GOTO ERROR
    END

    /* ERwin Builtin Trigger */
    /* ��Ʒ  ��Ӧ on child delete no action */
    /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="��Ʒ"
    CHILD_OWNER="", CHILD_TABLE="��Ӧ"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_40", FK_COLUMNS="��Ʒ��" */
    IF EXISTS (SELECT * FROM deleted,��Ʒ
      WHERE
        /* %JoinFKPK(deleted,��Ʒ," = "," AND") */
        deleted.��Ʒ�� = ��Ʒ.��Ʒ�� AND
        NOT EXISTS (
          SELECT * FROM ��Ӧ
          WHERE
            /* %JoinFKPK(��Ӧ,��Ʒ," = "," AND") */
            ��Ӧ.��Ʒ�� = ��Ʒ.��Ʒ��
        )
    )
    BEGIN
      SELECT @errno  = 30010,
             @errmsg = 'Cannot delete last ��Ӧ because ��Ʒ exists.'
      GOTO ERROR
    END

    /* ERwin Builtin Trigger */
    /* �ֿ�  ��Ӧ on child delete no action */
    /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="�ֿ�"
    CHILD_OWNER="", CHILD_TABLE="��Ӧ"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_42", FK_COLUMNS="�ֿ��" */
    IF EXISTS (SELECT * FROM deleted,�ֿ�
      WHERE
        /* %JoinFKPK(deleted,�ֿ�," = "," AND") */
        deleted.�ֿ�� = �ֿ�.�ֿ�� AND
        NOT EXISTS (
          SELECT * FROM ��Ӧ
          WHERE
            /* %JoinFKPK(��Ӧ,�ֿ�," = "," AND") */
            ��Ӧ.�ֿ�� = �ֿ�.�ֿ��
        )
    )
    BEGIN
      SELECT @errno  = 30010,
             @errmsg = 'Cannot delete last ��Ӧ because �ֿ� exists.'
      GOTO ERROR
    END


    /* ERwin Builtin Trigger */
    RETURN
ERROR:
    raiserror @errno @errmsg
    rollback transaction
END

go


CREATE TRIGGER tU_��Ӧ ON ��Ӧ FOR UPDATE AS
/* ERwin Builtin Trigger */
/* UPDATE trigger on ��Ӧ */
BEGIN
  DECLARE  @NUMROWS int,
           @nullcnt int,
           @validcnt int,
           @ins�̵�� integer, 
           @ins��Ʒ�� varchar(20), 
           @ins�ֿ�� integer,
           @errno   int,
           @errmsg  varchar(255)

  SELECT @NUMROWS = @@rowcount
  /* ERwin Builtin Trigger */
  /* �̵�  ��Ӧ on child update no action */
  /* ERWIN_RELATION:CHECKSUM="00039284", PARENT_OWNER="", PARENT_TABLE="�̵�"
    CHILD_OWNER="", CHILD_TABLE="��Ӧ"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_38", FK_COLUMNS="�̵��" */
  IF
    /* %ChildFK(" OR",UPDATE) */
    UPDATE(�̵��)
  BEGIN
    SELECT @nullcnt = 0
    SELECT @validcnt = count(*)
      FROM inserted,�̵�
        WHERE
          /* %JoinFKPK(inserted,�̵�) */
          inserted.�̵�� = �̵�.�̵��
    /* %NotnullFK(inserted," IS NULL","select @nullcnt = count(*) from inserted where"," AND") */
    
    IF @validcnt + @nullcnt != @NUMROWS
    BEGIN
      SELECT @errno  = 30007,
             @errmsg = 'Cannot update ��Ӧ because �̵� does not exist.'
      GOTO ERROR
    END
  END

  /* ERwin Builtin Trigger */
  /* ��Ʒ  ��Ӧ on child update no action */
  /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="��Ʒ"
    CHILD_OWNER="", CHILD_TABLE="��Ӧ"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_40", FK_COLUMNS="��Ʒ��" */
  IF
    /* %ChildFK(" OR",UPDATE) */
    UPDATE(��Ʒ��)
  BEGIN
    SELECT @nullcnt = 0
    SELECT @validcnt = count(*)
      FROM inserted,��Ʒ
        WHERE
          /* %JoinFKPK(inserted,��Ʒ) */
          inserted.��Ʒ�� = ��Ʒ.��Ʒ��
    /* %NotnullFK(inserted," IS NULL","select @nullcnt = count(*) from inserted where"," AND") */
    
    IF @validcnt + @nullcnt != @NUMROWS
    BEGIN
      SELECT @errno  = 30007,
             @errmsg = 'Cannot update ��Ӧ because ��Ʒ does not exist.'
      GOTO ERROR
    END
  END

  /* ERwin Builtin Trigger */
  /* �ֿ�  ��Ӧ on child update no action */
  /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="�ֿ�"
    CHILD_OWNER="", CHILD_TABLE="��Ӧ"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_42", FK_COLUMNS="�ֿ��" */
  IF
    /* %ChildFK(" OR",UPDATE) */
    UPDATE(�ֿ��)
  BEGIN
    SELECT @nullcnt = 0
    SELECT @validcnt = count(*)
      FROM inserted,�ֿ�
        WHERE
          /* %JoinFKPK(inserted,�ֿ�) */
          inserted.�ֿ�� = �ֿ�.�ֿ��
    /* %NotnullFK(inserted," IS NULL","select @nullcnt = count(*) from inserted where"," AND") */
    
    IF @validcnt + @nullcnt != @NUMROWS
    BEGIN
      SELECT @errno  = 30007,
             @errmsg = 'Cannot update ��Ӧ because �ֿ� does not exist.'
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




CREATE TRIGGER tD_��� ON ��� FOR DELETE AS
/* ERwin Builtin Trigger */
/* DELETE trigger on ��� */
BEGIN
  DECLARE  @errno   int,
           @errmsg  varchar(255)
    /* ERwin Builtin Trigger */
    /* �ֿ�  ��� on child delete no action */
    /* ERWIN_RELATION:CHECKSUM="0002051c", PARENT_OWNER="", PARENT_TABLE="�ֿ�"
    CHILD_OWNER="", CHILD_TABLE="���"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_25", FK_COLUMNS="�ֿ��" */
    IF EXISTS (SELECT * FROM deleted,�ֿ�
      WHERE
        /* %JoinFKPK(deleted,�ֿ�," = "," AND") */
        deleted.�ֿ�� = �ֿ�.�ֿ�� AND
        NOT EXISTS (
          SELECT * FROM ���
          WHERE
            /* %JoinFKPK(���,�ֿ�," = "," AND") */
            ���.�ֿ�� = �ֿ�.�ֿ��
        )
    )
    BEGIN
      SELECT @errno  = 30010,
             @errmsg = 'Cannot delete last ��� because �ֿ� exists.'
      GOTO ERROR
    END

    /* ERwin Builtin Trigger */
    /* ��Ʒ  ��� on child delete no action */
    /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="��Ʒ"
    CHILD_OWNER="", CHILD_TABLE="���"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_30", FK_COLUMNS="��Ʒ��" */
    IF EXISTS (SELECT * FROM deleted,��Ʒ
      WHERE
        /* %JoinFKPK(deleted,��Ʒ," = "," AND") */
        deleted.��Ʒ�� = ��Ʒ.��Ʒ�� AND
        NOT EXISTS (
          SELECT * FROM ���
          WHERE
            /* %JoinFKPK(���,��Ʒ," = "," AND") */
            ���.��Ʒ�� = ��Ʒ.��Ʒ��
        )
    )
    BEGIN
      SELECT @errno  = 30010,
             @errmsg = 'Cannot delete last ��� because ��Ʒ exists.'
      GOTO ERROR
    END


    /* ERwin Builtin Trigger */
    RETURN
ERROR:
    raiserror @errno @errmsg
    rollback transaction
END

go


CREATE TRIGGER tU_��� ON ��� FOR UPDATE AS
/* ERwin Builtin Trigger */
/* UPDATE trigger on ��� */
BEGIN
  DECLARE  @NUMROWS int,
           @nullcnt int,
           @validcnt int,
           @ins�ֿ�� integer, 
           @ins��Ʒ�� varchar(20),
           @errno   int,
           @errmsg  varchar(255)

  SELECT @NUMROWS = @@rowcount
  /* ERwin Builtin Trigger */
  /* �ֿ�  ��� on child update no action */
  /* ERWIN_RELATION:CHECKSUM="000259df", PARENT_OWNER="", PARENT_TABLE="�ֿ�"
    CHILD_OWNER="", CHILD_TABLE="���"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_25", FK_COLUMNS="�ֿ��" */
  IF
    /* %ChildFK(" OR",UPDATE) */
    UPDATE(�ֿ��)
  BEGIN
    SELECT @nullcnt = 0
    SELECT @validcnt = count(*)
      FROM inserted,�ֿ�
        WHERE
          /* %JoinFKPK(inserted,�ֿ�) */
          inserted.�ֿ�� = �ֿ�.�ֿ��
    /* %NotnullFK(inserted," IS NULL","select @nullcnt = count(*) from inserted where"," AND") */
    
    IF @validcnt + @nullcnt != @NUMROWS
    BEGIN
      SELECT @errno  = 30007,
             @errmsg = 'Cannot update ��� because �ֿ� does not exist.'
      GOTO ERROR
    END
  END

  /* ERwin Builtin Trigger */
  /* ��Ʒ  ��� on child update no action */
  /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="��Ʒ"
    CHILD_OWNER="", CHILD_TABLE="���"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_30", FK_COLUMNS="��Ʒ��" */
  IF
    /* %ChildFK(" OR",UPDATE) */
    UPDATE(��Ʒ��)
  BEGIN
    SELECT @nullcnt = 0
    SELECT @validcnt = count(*)
      FROM inserted,��Ʒ
        WHERE
          /* %JoinFKPK(inserted,��Ʒ) */
          inserted.��Ʒ�� = ��Ʒ.��Ʒ��
    /* %NotnullFK(inserted," IS NULL","select @nullcnt = count(*) from inserted where"," AND") */
    
    IF @validcnt + @nullcnt != @NUMROWS
    BEGIN
      SELECT @errno  = 30007,
             @errmsg = 'Cannot update ��� because ��Ʒ does not exist.'
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




CREATE TRIGGER tD_�̵� ON �̵� FOR DELETE AS
/* ERwin Builtin Trigger */
/* DELETE trigger on �̵� */
BEGIN
  DECLARE  @errno   int,
           @errmsg  varchar(255)
    /* ERwin Builtin Trigger */
    /* �̵�  ���� on parent delete no action */
    /* ERWIN_RELATION:CHECKSUM="0001b95e", PARENT_OWNER="", PARENT_TABLE="�̵�"
    CHILD_OWNER="", CHILD_TABLE="����"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_27", FK_COLUMNS="�̵��" */
    IF EXISTS (
      SELECT * FROM deleted,����
      WHERE
        /*  %JoinFKPK(����,deleted," = "," AND") */
        ����.�̵�� = deleted.�̵��
    )
    BEGIN
      SELECT @errno  = 30001,
             @errmsg = 'Cannot delete �̵� because ���� exists.'
      GOTO ERROR
    END

    /* ERwin Builtin Trigger */
    /* �̵�  ��Ӧ on parent delete no action */
    /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="�̵�"
    CHILD_OWNER="", CHILD_TABLE="��Ӧ"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_38", FK_COLUMNS="�̵��" */
    IF EXISTS (
      SELECT * FROM deleted,��Ӧ
      WHERE
        /*  %JoinFKPK(��Ӧ,deleted," = "," AND") */
        ��Ӧ.�̵�� = deleted.�̵��
    )
    BEGIN
      SELECT @errno  = 30001,
             @errmsg = 'Cannot delete �̵� because ��Ӧ exists.'
      GOTO ERROR
    END


    /* ERwin Builtin Trigger */
    RETURN
ERROR:
    raiserror @errno @errmsg
    rollback transaction
END

go


CREATE TRIGGER tU_�̵� ON �̵� FOR UPDATE AS
/* ERwin Builtin Trigger */
/* UPDATE trigger on �̵� */
BEGIN
  DECLARE  @NUMROWS int,
           @nullcnt int,
           @validcnt int,
           @ins�̵�� integer,
           @errno   int,
           @errmsg  varchar(255)

  SELECT @NUMROWS = @@rowcount
  /* ERwin Builtin Trigger */
  /* �̵�  ���� on parent update no action */
  /* ERWIN_RELATION:CHECKSUM="0001df7b", PARENT_OWNER="", PARENT_TABLE="�̵�"
    CHILD_OWNER="", CHILD_TABLE="����"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_27", FK_COLUMNS="�̵��" */
  IF
    /* %ParentPK(" OR",UPDATE) */
    UPDATE(�̵��)
  BEGIN
    IF EXISTS (
      SELECT * FROM deleted,����
      WHERE
        /*  %JoinFKPK(����,deleted," = "," AND") */
        ����.�̵�� = deleted.�̵��
    )
    BEGIN
      SELECT @errno  = 30005,
             @errmsg = 'Cannot update �̵� because ���� exists.'
      GOTO ERROR
    END
  END

  /* ERwin Builtin Trigger */
  /* �̵�  ��Ӧ on parent update no action */
  /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="�̵�"
    CHILD_OWNER="", CHILD_TABLE="��Ӧ"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_38", FK_COLUMNS="�̵��" */
  IF
    /* %ParentPK(" OR",UPDATE) */
    UPDATE(�̵��)
  BEGIN
    IF EXISTS (
      SELECT * FROM deleted,��Ӧ
      WHERE
        /*  %JoinFKPK(��Ӧ,deleted," = "," AND") */
        ��Ӧ.�̵�� = deleted.�̵��
    )
    BEGIN
      SELECT @errno  = 30005,
             @errmsg = 'Cannot update �̵� because ��Ӧ exists.'
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




CREATE TRIGGER tD_��Ʒ ON ��Ʒ FOR DELETE AS
/* ERwin Builtin Trigger */
/* DELETE trigger on ��Ʒ */
BEGIN
  DECLARE  @errno   int,
           @errmsg  varchar(255)
    /* ERwin Builtin Trigger */
    /* ��Ʒ  ��� on parent delete no action */
    /* ERWIN_RELATION:CHECKSUM="00027435", PARENT_OWNER="", PARENT_TABLE="��Ʒ"
    CHILD_OWNER="", CHILD_TABLE="���"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_30", FK_COLUMNS="��Ʒ��" */
    IF EXISTS (
      SELECT * FROM deleted,���
      WHERE
        /*  %JoinFKPK(���,deleted," = "," AND") */
        ���.��Ʒ�� = deleted.��Ʒ��
    )
    BEGIN
      SELECT @errno  = 30001,
             @errmsg = 'Cannot delete ��Ʒ because ��� exists.'
      GOTO ERROR
    END

    /* ERwin Builtin Trigger */
    /* ��Ʒ  ���� on parent delete no action */
    /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="��Ʒ"
    CHILD_OWNER="", CHILD_TABLE="����"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_32", FK_COLUMNS="��Ʒ��" */
    IF EXISTS (
      SELECT * FROM deleted,����
      WHERE
        /*  %JoinFKPK(����,deleted," = "," AND") */
        ����.��Ʒ�� = deleted.��Ʒ��
    )
    BEGIN
      SELECT @errno  = 30001,
             @errmsg = 'Cannot delete ��Ʒ because ���� exists.'
      GOTO ERROR
    END

    /* ERwin Builtin Trigger */
    /* ��Ʒ  ��Ӧ on parent delete no action */
    /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="��Ʒ"
    CHILD_OWNER="", CHILD_TABLE="��Ӧ"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_40", FK_COLUMNS="��Ʒ��" */
    IF EXISTS (
      SELECT * FROM deleted,��Ӧ
      WHERE
        /*  %JoinFKPK(��Ӧ,deleted," = "," AND") */
        ��Ӧ.��Ʒ�� = deleted.��Ʒ��
    )
    BEGIN
      SELECT @errno  = 30001,
             @errmsg = 'Cannot delete ��Ʒ because ��Ӧ exists.'
      GOTO ERROR
    END


    /* ERwin Builtin Trigger */
    RETURN
ERROR:
    raiserror @errno @errmsg
    rollback transaction
END

go


CREATE TRIGGER tU_��Ʒ ON ��Ʒ FOR UPDATE AS
/* ERwin Builtin Trigger */
/* UPDATE trigger on ��Ʒ */
BEGIN
  DECLARE  @NUMROWS int,
           @nullcnt int,
           @validcnt int,
           @ins��Ʒ�� varchar(20),
           @errno   int,
           @errmsg  varchar(255)

  SELECT @NUMROWS = @@rowcount
  /* ERwin Builtin Trigger */
  /* ��Ʒ  ��� on parent update no action */
  /* ERWIN_RELATION:CHECKSUM="0002e22f", PARENT_OWNER="", PARENT_TABLE="��Ʒ"
    CHILD_OWNER="", CHILD_TABLE="���"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_30", FK_COLUMNS="��Ʒ��" */
  IF
    /* %ParentPK(" OR",UPDATE) */
    UPDATE(��Ʒ��)
  BEGIN
    IF EXISTS (
      SELECT * FROM deleted,���
      WHERE
        /*  %JoinFKPK(���,deleted," = "," AND") */
        ���.��Ʒ�� = deleted.��Ʒ��
    )
    BEGIN
      SELECT @errno  = 30005,
             @errmsg = 'Cannot update ��Ʒ because ��� exists.'
      GOTO ERROR
    END
  END

  /* ERwin Builtin Trigger */
  /* ��Ʒ  ���� on parent update no action */
  /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="��Ʒ"
    CHILD_OWNER="", CHILD_TABLE="����"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_32", FK_COLUMNS="��Ʒ��" */
  IF
    /* %ParentPK(" OR",UPDATE) */
    UPDATE(��Ʒ��)
  BEGIN
    IF EXISTS (
      SELECT * FROM deleted,����
      WHERE
        /*  %JoinFKPK(����,deleted," = "," AND") */
        ����.��Ʒ�� = deleted.��Ʒ��
    )
    BEGIN
      SELECT @errno  = 30005,
             @errmsg = 'Cannot update ��Ʒ because ���� exists.'
      GOTO ERROR
    END
  END

  /* ERwin Builtin Trigger */
  /* ��Ʒ  ��Ӧ on parent update no action */
  /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="��Ʒ"
    CHILD_OWNER="", CHILD_TABLE="��Ӧ"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_40", FK_COLUMNS="��Ʒ��" */
  IF
    /* %ParentPK(" OR",UPDATE) */
    UPDATE(��Ʒ��)
  BEGIN
    IF EXISTS (
      SELECT * FROM deleted,��Ӧ
      WHERE
        /*  %JoinFKPK(��Ӧ,deleted," = "," AND") */
        ��Ӧ.��Ʒ�� = deleted.��Ʒ��
    )
    BEGIN
      SELECT @errno  = 30005,
             @errmsg = 'Cannot update ��Ʒ because ��Ӧ exists.'
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




CREATE TRIGGER tD_���� ON ���� FOR DELETE AS
/* ERwin Builtin Trigger */
/* DELETE trigger on ���� */
BEGIN
  DECLARE  @errno   int,
           @errmsg  varchar(255)
    /* ERwin Builtin Trigger */
    /* �̵�  ���� on child delete no action */
    /* ERWIN_RELATION:CHECKSUM="00020ce8", PARENT_OWNER="", PARENT_TABLE="�̵�"
    CHILD_OWNER="", CHILD_TABLE="����"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_27", FK_COLUMNS="�̵��" */
    IF EXISTS (SELECT * FROM deleted,�̵�
      WHERE
        /* %JoinFKPK(deleted,�̵�," = "," AND") */
        deleted.�̵�� = �̵�.�̵�� AND
        NOT EXISTS (
          SELECT * FROM ����
          WHERE
            /* %JoinFKPK(����,�̵�," = "," AND") */
            ����.�̵�� = �̵�.�̵��
        )
    )
    BEGIN
      SELECT @errno  = 30010,
             @errmsg = 'Cannot delete last ���� because �̵� exists.'
      GOTO ERROR
    END

    /* ERwin Builtin Trigger */
    /* ��Ʒ  ���� on child delete no action */
    /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="��Ʒ"
    CHILD_OWNER="", CHILD_TABLE="����"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_32", FK_COLUMNS="��Ʒ��" */
    IF EXISTS (SELECT * FROM deleted,��Ʒ
      WHERE
        /* %JoinFKPK(deleted,��Ʒ," = "," AND") */
        deleted.��Ʒ�� = ��Ʒ.��Ʒ�� AND
        NOT EXISTS (
          SELECT * FROM ����
          WHERE
            /* %JoinFKPK(����,��Ʒ," = "," AND") */
            ����.��Ʒ�� = ��Ʒ.��Ʒ��
        )
    )
    BEGIN
      SELECT @errno  = 30010,
             @errmsg = 'Cannot delete last ���� because ��Ʒ exists.'
      GOTO ERROR
    END


    /* ERwin Builtin Trigger */
    RETURN
ERROR:
    raiserror @errno @errmsg
    rollback transaction
END

go


CREATE TRIGGER tU_���� ON ���� FOR UPDATE AS
/* ERwin Builtin Trigger */
/* UPDATE trigger on ���� */
BEGIN
  DECLARE  @NUMROWS int,
           @nullcnt int,
           @validcnt int,
           @ins�̵�� integer, 
           @ins��Ʒ�� varchar(20),
           @errno   int,
           @errmsg  varchar(255)

  SELECT @NUMROWS = @@rowcount
  /* ERwin Builtin Trigger */
  /* �̵�  ���� on child update no action */
  /* ERWIN_RELATION:CHECKSUM="00027877", PARENT_OWNER="", PARENT_TABLE="�̵�"
    CHILD_OWNER="", CHILD_TABLE="����"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_27", FK_COLUMNS="�̵��" */
  IF
    /* %ChildFK(" OR",UPDATE) */
    UPDATE(�̵��)
  BEGIN
    SELECT @nullcnt = 0
    SELECT @validcnt = count(*)
      FROM inserted,�̵�
        WHERE
          /* %JoinFKPK(inserted,�̵�) */
          inserted.�̵�� = �̵�.�̵��
    /* %NotnullFK(inserted," IS NULL","select @nullcnt = count(*) from inserted where"," AND") */
    
    IF @validcnt + @nullcnt != @NUMROWS
    BEGIN
      SELECT @errno  = 30007,
             @errmsg = 'Cannot update ���� because �̵� does not exist.'
      GOTO ERROR
    END
  END

  /* ERwin Builtin Trigger */
  /* ��Ʒ  ���� on child update no action */
  /* ERWIN_RELATION:CHECKSUM="00000000", PARENT_OWNER="", PARENT_TABLE="��Ʒ"
    CHILD_OWNER="", CHILD_TABLE="����"
    P2C_VERB_PHRASE="", C2P_VERB_PHRASE="", 
    FK_CONSTRAINT="R_32", FK_COLUMNS="��Ʒ��" */
  IF
    /* %ChildFK(" OR",UPDATE) */
    UPDATE(��Ʒ��)
  BEGIN
    SELECT @nullcnt = 0
    SELECT @validcnt = count(*)
      FROM inserted,��Ʒ
        WHERE
          /* %JoinFKPK(inserted,��Ʒ) */
          inserted.��Ʒ�� = ��Ʒ.��Ʒ��
    /* %NotnullFK(inserted," IS NULL","select @nullcnt = count(*) from inserted where"," AND") */
    
    IF @validcnt + @nullcnt != @NUMROWS
    BEGIN
      SELECT @errno  = 30007,
             @errmsg = 'Cannot update ���� because ��Ʒ does not exist.'
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



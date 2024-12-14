import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';
import { Observable, Subject } from 'rxjs';
import { StringIds, StringIdsType } from 'src/stringIds';
import { TranslateService } from '@ngx-translate/core';
import { GetTodoModel, GetTodosModel, TodosModel, TodosService } from '@services/todos';
import { TableColumnModel, TableDataModel, TableElementType, TableModel, TableRowModel } from '@patterns/table';
import { ButtonModel, ButtonTypeEnum } from '@patterns/button';
import { DialogConfigData, DialogModel } from '@patterns/dialog';
import { MatDialog, MatDialogConfig } from '@angular/material/dialog';
import { AddTodoComponent } from './addTodo/addTodo.component';
import { DialogService } from '@patterns/dialog/dialog.service';
import { clickListenerEvent } from '../../patterns/common.model';
import { UpdateTodoComponent } from './updateTodos/updateTodo.component';


@Component({
  selector: 'feature-todos',
  templateUrl: './todos.component.html',
  styleUrls: ['./todos.component.css'],
})
export class TodosComponent implements OnInit {
  @Input() public homepage: TodosModel;

  @Output() clickListener = new EventEmitter();
  @Output() contentComponentData: EventEmitter<any> = new EventEmitter<any>();
  sub : Subject<any> = new Subject<any>();

  public getTodosModel: GetTodosModel = null;
  public tableModel: TableModel;
  public dialogModel: DialogModel;
  constructor(
    private translate: TranslateService,
    private todosService: TodosService,
    private dialogService: DialogService,
    
  ) {
    

  }

  ngOnInit(): void {
    this.getTodos();
    
    
  }
  getTodos() {
    this.todosService.get(GetTodosModel, "?includeMembers=true").subscribe((res: GetTodosModel) => {
      this.getTodosModel = res;
      this.updateTableData();
    });
  }

  updateTableData() {
    const columns: TableColumnModel[] = [
      new TableColumnModel("title", StringIds.cTODO_TITLE, "title"),
      new TableColumnModel("status", StringIds.cSTATUS, "status"),
      new TableColumnModel("description", StringIds.cDESCRIPTION, "description"),
      new TableColumnModel("updateButton", StringIds.cUPDATE, "button"),
      new TableColumnModel("deleteButtonutton", StringIds.cDELETE, "button")
    ];
    const tableData: TableRowModel[] = [];
    let deleteButton:ButtonModel;
    let updateButton:ButtonModel;
    let memberIndex = 0;
    this.getTodosModel.members.forEach(
      (member) => {
        deleteButton = new ButtonModel();
        deleteButton.setButtonValues(StringIds.cDELETE, ButtonTypeEnum.DELETE, member.id, (event) => {this.deleteTodo(`/${member.id}`)});
        updateButton = new ButtonModel();
        updateButton.setButtonValues(StringIds.cUPDATE, ButtonTypeEnum.PRIMARY, member.id, (event) => {this.updateTodo(member)});
        const data: TableDataModel[] = [
          new TableDataModel("title", "title", member.title, TableElementType.TEXT),
          new TableDataModel("status", "status", member.status, TableElementType.TEXT),
          new TableDataModel("description", "description", member.description, TableElementType.TEXT),
          new TableDataModel("button", "button", updateButton, TableElementType.BUTTON),
          new TableDataModel("button", "button", deleteButton, TableElementType.BUTTON)
        ];
        const row: TableRowModel = new TableRowModel();
        row.data = data;
        tableData.push(row);
        memberIndex++;
      }
    );
    this.tableModel = new TableModel();
    this.tableModel.id = "todosTable";
    this.tableModel.title = StringIds.cTODOS;
    this.tableModel.columns = columns;
    this.tableModel.rows = tableData;
    const addButton = new ButtonModel();
    addButton.setButtonValues(StringIds.cADD_TODO, ButtonTypeEnum.PRIMARY, "addButton", (event) => {this.onClicked(event)});
    this.tableModel.actionButtons = [
      addButton
    ];
  }

  deleteTodo(id:string){
    this.todosService.delete(TodosModel, id).subscribe((res) => {
      this.getTodos();
    });
  }

  onClicked(event: Event) {
    let d = new DialogConfigData();
    d.contentComponentData = new TodosModel({
      "title": "Hello",
      "description": "World"
    })
    d.contentComponentEvent = this.sub;
    let dialogRef = this.dialogService.open(AddTodoComponent, d);
    this.sub.subscribe((event: clickListenerEvent) => {
      console.log(event);
      dialogRef.close();
    });
    dialogRef.afterClosed().subscribe(result => {
      this.getTodos();
    });
  }

  updateTodo(todo: GetTodoModel) {
    let dialogConfigData = new DialogConfigData();
    dialogConfigData.contentComponentData = todo;
    dialogConfigData.contentComponentEvent = this.sub;
    let dialogRef = this.dialogService.open(UpdateTodoComponent, dialogConfigData);
    this.sub.subscribe((event: clickListenerEvent) => {
      console.log(event);
      dialogRef.close();
    });
    dialogRef.afterClosed().subscribe(result => {
      this.getTodos();
    });
  }
  public getLocalizedString$(stringId: StringIdsType): Observable<string> {
    return this.translate.stream(stringId);
  }
}

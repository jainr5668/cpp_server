import { CommonModule } from '@angular/common';
import { NgModule } from '@angular/core';
import { TranslateModule } from "@ngx-translate/core";
import { TodosRoutingModule } from './todos.routing.module';
import { CardModule } from '@patterns/card';
import { TodosComponent } from './todos.component';
import { TableModule } from '@patterns/table';
import { DialogModule } from '@patterns/dialog/dialog.module';
import { AddTodoComponent } from './addTodo/addTodo.component';
import { MatDialogModule } from '@angular/material/dialog';
import { UpdateTodoComponent } from './updateTodos/updateTodo.component';

@NgModule({
  declarations: [TodosComponent, AddTodoComponent, UpdateTodoComponent],
  imports: [
    CardModule,
    CommonModule,
    TranslateModule,
    TodosRoutingModule,
    TableModule,
    DialogModule,
    MatDialogModule 
  ],
  exports: [TodosComponent],
})
export class TodosModule {}
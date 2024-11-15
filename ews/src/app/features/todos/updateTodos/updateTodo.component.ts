import { Component, OnInit, Input, Output, EventEmitter, Inject } from '@angular/core';
import { Observable, Subject } from 'rxjs';
import { StringIds, StringIdsType } from 'src/stringIds';
import { TranslateService } from '@ngx-translate/core';
import { GetTodoModel, GetTodosModel, TodosModel, TodosService } from '@services/todos';
import { TableColumnModel, TableDataModel, TableElementType, TableModel, TableRowModel } from '@patterns/table';
import { ButtonModel, ButtonTypeEnum } from '@patterns/button';
import { DialogConfigData, DialogModel } from '@patterns/dialog';
import { SignupComponent } from '@features/auth/signup';
import { MatDialog, MatDialogConfig, MAT_DIALOG_DATA } from '@angular/material/dialog';
import { CardModel } from '@patterns/card';
import { ContentModel } from '@patterns/content';
import { ElementModel } from '@patterns/element';
import { FooterModel, FooterTypeEnum } from '@patterns/footer';
import { ThisReceiver } from '@angular/compiler';
import { SelectOption } from '../../../patterns/element/element.model';


@Component({
    selector: 'feature-todos-updateTodo',
    templateUrl: './updateTodo.component.html',
    styleUrls: ['./updateTodo.component.css'],
})
export class UpdateTodoComponent implements OnInit {

    card: CardModel;
    todosData: GetTodoModel;
    constructor(
        private translate: TranslateService,
        private todosService: TodosService,
        @Inject(MAT_DIALOG_DATA) public dialogConfigData: DialogConfigData
    ) {
        
    }

    ngOnInit(): void {
        this.todosData = <GetTodoModel>this.dialogConfigData.contentComponentData;
        this.createUpdateTodoCard();
    }

    createUpdateTodoCard() {
        const elements = [];

        // Title
        let element = new ElementModel();
        element.textField("title", StringIds.cTODO_TITLE, this.todosData, "title");
        element.colspan = 1;
        elements.push(element);

        // Due Date
        element = new ElementModel();
        element.textField("due-date", StringIds.cDUE_DATE, this.todosData, "dueDate");
        element.colspan = 1;
        elements.push(element);

        // Description
        element = new ElementModel();
        element.textField("description", StringIds.cDESCRIPTION, this.todosData, "description");
        element.colspan = 2;
        elements.push(element);

        // Status
        const selectOptions: SelectOption[] = [
            new SelectOption("pending", StringIds.cPENDING),
            new SelectOption("completed", StringIds.cCOMPLETED)
        ];
        element = new ElementModel();
        element.select("status", StringIds.cSTATUS, this.todosData, "status", selectOptions);
        element.colspan = 1;
        elements.push(element);

        // Content
        const contentModel = new ContentModel();
        contentModel.setContentValues("update-todo", StringIds.cUPDATE_TODO);
        contentModel.cols = 2;
        contentModel.elements = elements;

        // Card
        this.card = new CardModel();
        this.card.contents = [contentModel];
        this.card.footer = new FooterModel(FooterTypeEnum.APPLY_CANCEL, "update-todo", null, (event) => { this.updateTodoEvent(event) });
    }
    updateTodoEvent(event) {
        if (event.id == "update-todo-cancel-button") { }
        else if (event.id == "update-todo-apply-button") {
            this.todosService.patch(GetTodoModel, this.todosData, `/${this.todosData.id}`).subscribe();
        }
        this.dialogConfigData.contentComponentEvent.next(event);
    }
}
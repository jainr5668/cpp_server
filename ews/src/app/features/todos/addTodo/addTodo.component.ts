import { Component, OnInit, Input, Output, EventEmitter, Inject } from '@angular/core';
import { Observable, Subject } from 'rxjs';
import { StringIds, StringIdsType } from 'src/stringIds';
import { TranslateService } from '@ngx-translate/core';
import { GetTodosModel, TodosModel, TodosService } from '@services/todos';
import { TableColumnModel, TableDataModel, TableElementType, TableModel, TableRowModel } from '@patterns/table';
import { ButtonModel, ButtonTypeEnum } from '@patterns/button';
import { DialogConfigData, DialogModel } from '@patterns/dialog';
import { SignupComponent } from '@features/auth/signup';
import { MatDialog, MatDialogConfig, MAT_DIALOG_DATA } from '@angular/material/dialog';
import { CardModel } from '@patterns/card';
import { ContentModel } from '@patterns/content';
import { ElementModel } from '@patterns/element';
import { FooterModel, FooterTypeEnum } from '@patterns/footer';


@Component({
    selector: 'feature-todos-addTodo',
    templateUrl: './addTodo.component.html',
    styleUrls: ['./addTodo.component.css'],
})
export class AddTodoComponent implements OnInit {

    card: CardModel;
    todosData:TodosModel = new TodosModel();
    constructor(
        private translate: TranslateService,
        private todosService: TodosService,
        @Inject(MAT_DIALOG_DATA) public data: DialogConfigData
    ) {
        
    }

    ngOnInit(): void {
        this.createAddTodoCard();
        console.log(this.data);
    }
    createAddTodoCard() {
        const elements = [];
        let element = new ElementModel();

        // Title
        element.textField("title", StringIds.cTODO_TITLE, this.todosData, "title");
        element.colspan = 1;
        elements.push(element);

        // Description
        element = new ElementModel();
        element.textField("description", StringIds.cDESCRIPTION, this.todosData, "description");
        element.colspan = 1;
        elements.push(element);
        const content:ContentModel = new ContentModel();
        content.setContentValues("add-todo-content", StringIds.cADD_TODO);
        content.cols = 2;
        content.elements = elements;
        this.card = new CardModel();
        this.card.contents = [content];
        this.card.footer = new FooterModel(FooterTypeEnum.APPLY_CANCEL, "add-todo", null, (event)=>{this.addTodoEvent(event)});
    }

    addTodoEvent(event: any) {
        if (event.id === "add-todo-cancel-button"){

        }
        else if (event.id === "add-todo-apply-button") {
            this.todosService.post(TodosModel, this.todosData).subscribe((res: any) => {
                
            });
        }
        this.data.contentComponentEvent.next(event);
    }
}
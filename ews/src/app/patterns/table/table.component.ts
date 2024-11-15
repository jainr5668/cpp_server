import { Component, EventEmitter, Input, OnInit, Output } from "@angular/core";
import { ButtonModel } from "@patterns/button";
import { clickListenerEvent } from "@patterns/common.model";
import { TableModel, TableElementType } from "./table.model";
import { Observable } from "rxjs";
import { StringIdsType } from "src/stringIds";
import { TranslateService } from "@ngx-translate/core";
import { FormControl, FormGroup } from "@angular/forms";

@Component({
  selector: 'pattern-table',
  templateUrl: './table.component.html',
  styleUrls: ['./table.component.css'],
})
export class TableComponent implements OnInit {
  @Input() public table: TableModel;
  @Output() clickListener = new EventEmitter();

  tableElementType = TableElementType;
  formGroup: FormGroup;
  constructor(private translate: TranslateService){
  }

  ngOnInit(): void {
    this.formGroup = new FormGroup({});
    this.table.rows.forEach((row) => {
      row.data.forEach((data) => {
        if (data.type === TableElementType.ELEMENT) {
          console.log(data.data);
          this.formGroup.addControl(data.data.id, new FormControl(''));
        }
      });
    });
  }
  
  public getLocalizedString$(stringId: StringIdsType): Observable<string> {
    return this.translate.stream(stringId);
  }
  onClicked(event: Event){
    if (this.table.event) {
      this.table.event(event);
    } else {
      this.clickListener.emit(event);
    }
  }
}
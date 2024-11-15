import { Component, OnInit, Input, Output, EventEmitter } from "@angular/core";
import { FormControl, FormGroup } from "@angular/forms";
import { TranslateService } from "@ngx-translate/core";
import { clickListenerEvent } from "@patterns/common.model";
import { Observable, map } from "rxjs";
import { StringIds, StringIdsType } from "src/stringIds";
import { ContentModel } from "./content.model";
import { STRING_TYPE } from "@angular/compiler";

@Component({
  selector: 'pattern-content',
  templateUrl: './content.component.html',
  styleUrls: ['./content.component.css'],
})
export class ContentComponent implements OnInit {
  @Input() public content: ContentModel;

  @Output() clickListener = new EventEmitter();

  formGroup: FormGroup;

  counterData = {
    row: 0,
    col: 0,
  };

  constructor(private translate: TranslateService) {
    this.formGroup = new FormGroup({});
  }

  public getLocalizedString$(stringId: string | string[]): Observable<string> {
    return this.translate.stream(stringId);
  }

  ngOnInit(): void {
    this.counterData.col = this.content.cols;
    this.counterData.row = this.content.elements.length / this.content.cols;
    this.content.elements.forEach((element) => {
      this.formGroup.addControl(element.id, new FormControl(''));
    });
  }
  counter(count: number) {
    const dummyList = [];
    for (let i = 0; i < count; i++) {
      dummyList.push(i);
    }
    return dummyList;
  }
  getIndex(i: number, j: number): number {
    return i * this.counterData.col + j;
  }

  onClicked(event: Event) {
    const eventObject = new clickListenerEvent(event, this.content.id);
    if (this.content.event) {
      this.content.event(eventObject);
    } else {
      this.clickListener.emit(eventObject);
    }
  }
}

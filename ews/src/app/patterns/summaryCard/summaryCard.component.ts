import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';
import { Observable } from 'rxjs';
import { StringIds, StringIdsType } from 'src/stringIds';
import { TranslateService } from '@ngx-translate/core';
import { SummaryCardModel } from './summaryCard.model';

@Component({
  selector: 'pattern-summaryCard',
  templateUrl: './summaryCard.component.html',
  styleUrls: ['./summaryCard.component.css'],
})
export class SummaryCardComponent implements OnInit {
  @Input() public summaryCardModel: SummaryCardModel;

  @Output() clickListener = new EventEmitter();

  constructor(
    private translate: TranslateService
  ) {}

  ngOnInit(): void {
  }

  public getLocalizedString$(stringId: StringIdsType): Observable<string> {
    return this.translate.stream(stringId);
  }
}
